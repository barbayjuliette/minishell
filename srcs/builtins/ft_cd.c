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

void	update_env(t_data *data)
{
	int		i;
	int		k;
	char	*path;
	char	*new;

	i = 0;
	path = getcwd(NULL, 0);
	if (!path)
		return ;
	new = ft_strjoin("PWD=", path);
	free(path);
	k = find_name(new, data);
	while (data->envp[i])
	{
		if (i == k)
		{
			create_token(0, new, &data->cd_names);
			data->envp[i] = new;
			data->ft_cd_flag = 1;
		}
		i++;
	}
}

int	ft_empty_cd(t_data *data)
{
	int		res;
	char	*home_path;

	home_path = getenv("HOME");
	if (home_path == NULL)
	{
		ft_putstr_fd("HOME environment variable not set\n", 2);
		return (1);
	}
	res = chdir(home_path);
	update_env(data);
	return (res);
}

int	ft_cd(char **args, t_data *data)
{
	int	res;

	if (!args[1])
		return (ft_empty_cd(data));
	if (args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		data->exit_code = 1;
		return (1);
	}
	else
		res = chdir(args[1]);
	if (res != 0)
	{
		data->exit_code = 1;
		perror(args[1]);
		return (1);
	}
	update_env(data);
	return (0);
}
