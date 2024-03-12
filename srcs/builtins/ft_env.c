/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:11:37 by akolgano          #+#    #+#             */
/*   Updated: 2024/03/11 18:41:36 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
extern int	g_status;

int	ft_env(char **args, t_data *data)
{
	int		i;
	char	*env_value;

	i = 0;
	(void)args;
	if (args[1])
	{
		write(STDERR_FILENO, "minishell: env: too many args\n", 31);
		g_status = 1;
		return (0);
	}
	env_value = ft_getenv("PATH", data);
	if (!env_value)
	{
		ft_putendl_fd("env: No such file or directory", STDOUT_FILENO);
		g_status = 127;
		return (127);
	}
	while (data->envp[i])
	{
		ft_putendl_fd(data->envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
