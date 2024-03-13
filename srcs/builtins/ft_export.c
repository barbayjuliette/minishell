/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:02:32 by akolgano          #+#    #+#             */
/*   Updated: 2024/03/13 14:19:36 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	change_value(char *name, t_data *data, char *full)
{
	int	i;
	char *env_name;

	i = 0;
	while (data->envp[i])
	{
		env_name = get_name(data->envp[i]);
		if (ft_compare1(name, env_name) == 0)
		{			
			data->envp[i] = ft_strdup(full);
			free(env_name);
			break ;
		}
		else
			i++;
		free(env_name);
	}
	return (0);
}

int	add_new_var(char *name, t_data *data, char *full)
{
	add_new_name(name, data);
	change_value(name, data, full);
	return (0);
}

char	*ft_getenv(char *name, t_data *data)
{
	int	i;
	char *env_name;

	i = 0;
	while (data->envp[i])
	{
		env_name = get_name(data->envp[i]);
		if (ft_compare1(name, env_name) == 0)
		{
			free(env_name);
			return (get_value(data->envp[i]));
		}
		else
			i++;
		free(env_name);
	}
	return (ft_strdup(""));
}

int	check_if_exist(char *name, t_data *data)
{
	int	i;
	char *env_name;

	i = 0;
	while (data->envp[i])
	{
		env_name = get_name(data->envp[i]);
		if (ft_compare1(name, env_name) == 0)
		{
			free(env_name);
			return (1);
		}
		else
			i++;
		free(env_name);
	}
	return (0);
}

int	ft_export(char **args, t_data *data)
{
	int		len_name;
	int		exist;
	char	*equal_sign_pos;
	char	*name;

	if (!args[1])
		return (print_env(data));
	equal_sign_pos = ft_strchr(args[1], '=');
	if (!equal_sign_pos)
		len_name = ft_strlen(args[1]);
	else
		len_name = equal_sign_pos - args[1];
	name = (char *)malloc(len_name + 1);
	ft_strlcpy(name, args[1], len_name);
	exist = check_if_exist(name, data);
	if (var_is_valid(name) == -1)
	{
		free(name);
		return (1);
	}
	if (!exist)
	{
		add_new_var(name, data, args[1]);
		return (0);
	}
	if (equal_sign_pos)
		change_value(name, data, args[1]);
	free(name);
	return (0);
}
