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
	i = -1;
	while (++i < 2 * data->number_of_commands)
		close(pipefds[i]);
	if (data->blocking_flag == 1 && (!ft_compare1(table->cmds[0], "cat") || \
		!ft_compare1(table->cmds[0], "grep" ) || \
		!ft_compare1(table->cmds[0], "wc" )) && data->infile == 0)
		handle_error_blocking(table->cmds, data);
	else
		execute_node(table->cmds, data);
	return (0);
}

/*int	process(int *pipefds, t_cmd_table *table, t_data *data)
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
		data->exit_code = 0;
		while (get_fd(table, data) == 1)
		{
			if (table->next)
				table = table->next;
			else
			{
				data->exit_code = 1;
				return (1);
			}
			data->blocking_flag = 1;
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
}*/
void	setup_pipes(int *pipefds, t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->number_of_commands))
	{
		if (pipe(pipefds + i * 2) < 0)
			exit(EXIT_FAILURE);
		i++;
	}
}

int	execute_commands(int *pipefds, t_cmd_table *table, t_data *data, int j)
{
	pid_t	pid;

	while (table)
	{
		data->exit_code = 0;
		while (get_fd(table, data) == 1)
		{
			if (table->next)
				table = table->next;
			else
			{
				data->exit_code = 1;
				return (1);
			}
			data->blocking_flag = 1;
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

int	process(int *pipefds, t_cmd_table *table, t_data *data)
{
	setup_pipes(pipefds, data);
	return execute_commands(pipefds, table, data, 0);
}

int	create_process(t_cmd_table *table, t_data *data)
{
	int		*pipefds;
	int		status;
	int		i;

	status = 0;
	pipefds = malloc(sizeof(int) * (2 * data->number_of_commands));
	data->pipefds = pipefds;
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
		if (WIFEXITED(status) && data->exit_code != 1)
			data->exit_code = WEXITSTATUS(status);
		i++;
	}
	free(pipefds);
	return (0);
}

int	execute(t_cmd_table *original_table, t_data *data)
{
	int			i;
	t_cmd_table	*table;

	table = original_table;
	data->tbl = original_table;
	data->outfile = STDOUT_FILENO;
	data->infile = STDIN_FILENO;
	get_number_of_commands(table, data);
	if (table->input)
		run_heredoc(table, data);
	i = check_if_builtins(table->cmds[0], data);
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
