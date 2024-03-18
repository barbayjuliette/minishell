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

int	check_if_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(char **args, t_data *data)
{
	long	err;

	data->exit_flag = 0;
	write(STDOUT_FILENO, "exit\n", 5);
	if (args[1])
	{
		if (args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			data->exit_code = 1;
			return (1);
		}
		if (check_if_str(args[1]) == 1)
		{
			ft_putstr_fd("minishell: numeric argument required\n", 2);
			data->exit_code = 2;
			return (1);
		}
		err = ft_atoi(args[1]);
		data->exit_code = err % 256;
		return (1);
	}
	return (0);
}
