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
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_IGN);
	if (execve(path, cmd, data->envp) == -1)
		handle_error(cmd, path, data);
}
