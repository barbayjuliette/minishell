/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:56:49 by akolgano          #+#    #+#             */
/*   Updated: 2024/02/27 17:56:51 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (cmd);
}

void	handle_error(char **cmd, char	*path, t_data *data)
{
	ft_putstr_fd(cmd[0], 2);
	ft_putendl_fd(": command not found", 2);
	if (path != cmd[0])
		free(path);
	free(data->pipefds);
	free_tokens(&data->tokens, 1);
	free_commands(&data->tbl);
	exit(127);
}

void	ft_execve(char **cmd, t_data *data)
{
	char	*path;
	char	*env_value;

	env_value = ft_getenv_for_env("PATH", data);
	if (!env_value)
	{
		path = cmd[0];
		data->exit_code = 1;
	}
	else
		path = find_path(cmd[0], data->envp);
	free(env_value);
	if (!path)
	{
		free(cmd);
		ft_putstr_fd(cmd[0], 2);
		data->exit_code = 1;
		ft_putendl_fd(": command not found", 2);
	}
	if (execve(path, cmd, data->envp) == -1)
		handle_error(cmd, path, data);
}

int	process(int *pipefds, t_cmd_table *table, t_data *data)
{
	setup_pipes(pipefds, data);
	setup_signals();
	return (execute_commands(pipefds, table, data, 0));
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
