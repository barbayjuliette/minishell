/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:02:38 by akolgano          #+#    #+#             */
/*   Updated: 2024/02/27 16:02:39 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
extern int	g_status;

int	ft_exit(char **args, t_data *data)
{
	data->exit_flag = 0;
	write(STDOUT_FILENO, "exit\n", 5);
	if (args[1])
	{
		write(STDERR_FILENO, "minishell: exit: too many args\n", 32);
		g_status = 1;
		return (1);
	}
	return (0);
}
