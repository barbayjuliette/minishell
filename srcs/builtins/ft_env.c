/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:11:37 by akolgano          #+#    #+#             */
/*   Updated: 2024/03/13 10:50:14 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_path(t_data *data)
{
	char	*env_value;

	env_value = ft_getenv_for_env("PATH", data);
	if (!env_value)
	{
		ft_putendl_fd("env: command not found", STDOUT_FILENO);
		data->exit_code = 127;
		return (127);
	}
	free(env_value);
	return (0);
}

int	ft_env(char **args, t_data *data)
{
	int		i;

	i = 0;
	if (args[1])
	{
		write(STDERR_FILENO, "minishell: env: too many args\n", 31);
		data->exit_code = 1;
		return (0);
	}
	if (check_for_path(data))
		return (127);
	while (data->envp[i])
	{
		if (check_name(data->envp[i], 1) == 5)
		{
			i ++;
			continue ;
		}
		ft_putendl_fd(data->envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
