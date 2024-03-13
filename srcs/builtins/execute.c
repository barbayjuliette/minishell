/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:05:10 by akolgano          #+#    #+#             */
/*   Updated: 2024/02/27 14:05:11 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_node(char **cmds, t_data *data)
{
	int		i;
	char	*name;

	name = cmds[0];
	i = check_if_builtins(name, data);
	if (i < NUM_BULTINS)
		ft_callbuiltin(i, cmds, data);
	else
		ft_execve(cmds, data);
	return (0);
}

int	execute_process(int *pipefds, t_cmd_table *table, t_data *data, int j)
{
	int	i;

	dup2(data->infile, STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	if (table->next && data->outfile == 1)
	{
		if (dup2(pipefds[j + 1], 1) < 0)
			exit(EXIT_FAILURE);
	}
	if (j != 0 && data->infile == 0)
	{
		if (dup2(pipefds[j - 2], 0) < 0)
			exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < 2 * data->number_of_commands)
	{
		close(pipefds[i]);
		i++;
	}
	execute_node(table->cmds, data);
	return (0);
}

int	process(int *pipefds, t_cmd_table *table, t_data *data)
{
	int		i;
	int		j;
	pid_t	pid;

	i = 0;
	while (i < (data->number_of_commands))
	{
		if (pipe(pipefds + i * 2) < 0)
			exit(EXIT_FAILURE);
		i++;
	}
	j = 0;
	while (table)
	{
		while (get_fd(table, data) == 1)
		{
			if (table->next)
				table = table->next;
			else
			{				
				data->exit_code = 1;
				return(1) ;
			}
		}
		pid = fork();
		if (pid == 0)
			execute_process(pipefds, table, data, j);
		else if (pid < 0)
			exit(EXIT_FAILURE);
		table = table->next;
		j += 2;
	}
	return (0);
}

int	create_process(t_cmd_table *table, t_data *data)
{
	int		*pipefds;
	int		status;
	int		i;
	int exit_code;

	pipefds = malloc(sizeof(int) * (2 * data->number_of_commands));
	process(pipefds, table, data);
	i = 0;
	while (i < 2 * data->number_of_commands)
	{
		close(pipefds[i]);
		i++;
	}
	i = 0;
	while (i < data->number_of_commands + 1)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			if (data->exit_code != 1)
				data->exit_code = WEXITSTATUS(status);
		}
		i++;
	}
	free(pipefds);
	return (0);
}

int	execute(t_cmd_table *table, t_data *data)
{
	int		i;
	char	*name;

	name = table->cmds[0];
	data->outfile = STDOUT_FILENO;
	data->infile = STDIN_FILENO;
	if (table->input)
		run_heredoc(table, data);
	i = check_if_builtins(name, data);
	if (data->number_of_commands == 1 && i < 7)
	{
		if (get_fd(table, data) != 1)
			execute_single_command(i, table->cmds, data);
		else
			data->exit_code = 1;
	}
	else
	{
		create_process(table, data);
		close(data->outfile);
	}
	return (0);
}
