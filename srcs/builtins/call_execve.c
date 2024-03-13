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

void	ft_execve(char **cmd, t_data *data)
{
	char	*path;
	char	*env_value;
	int i;

	env_value = ft_getenv("PATH", data);
	if (!env_value)
	{
		path = cmd[0];
		data->exit_code = 1;
		ft_putendl_fd("env: No such file or directory", STDOUT_FILENO);
	}
	else
		path = find_path(cmd[0], data->envp);
	free(env_value);
	i = -1;
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		ft_putstr_fd(cmd[0], 2);
		data->exit_code = 1;
		ft_putendl_fd(": No such file or directory", 2);
	}
	signal(SIGQUIT, SIG_DFL); // CTRL+\.
	signal(SIGINT, SIG_IGN); // CTRL+C
	if (execve(path, cmd, data->envp) == -1)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}
