/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:44:41 by akolgano          #+#    #+#             */
/*   Updated: 2024/02/27 17:44:45 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_path_to_env(t_data *data)
{
	int		i;
	char	*tmp;
	char	pwd[PATH_MAX];
	char	*str;

	i = 0;
	str = getcwd(pwd, PATH_MAX);
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", str);
			data->envp[i] = tmp;
			free(tmp);
		}
		i++;
	}
}

int	ft_cd(char **args, t_data *data)
{
	int		res;
	char	*home_path;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		home_path = getenv("HOME");
		if (home_path == NULL)
		{
			ft_putstr_fd("HOME environment variable not set\n", STDERR_FILENO);
			return (1);
		}
		res = chdir(home_path);
	}
	else
		res = chdir(args[1]);
	if (res != 0)
	{
		ft_putstr_fd(args[1], STDERR_FILENO);
		perror(": ");
		return (1);
	}
	add_path_to_env(data);
	return (0);
}
