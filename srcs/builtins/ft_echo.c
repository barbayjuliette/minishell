/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:06:15 by akolgano          #+#    #+#             */
/*   Updated: 2024/02/27 15:06:16 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (*s1 && *s2 && *s1 == *s2)
		s1 += (++s2 || 1);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_echo(char **args, t_data *data)
{
	char	is_n;
	int		i;

	is_n = 0;
	i = 1;
	(void)data;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		is_n = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			ft_putstr_fd(" ", 1);
		if (!args[i])
			break ;
	}
	if (!is_n)
		ft_putstr_fd("\n", 1);
	return (0);
}
