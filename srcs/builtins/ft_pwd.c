/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:38:16 by akolgano          #+#    #+#             */
/*   Updated: 2024/02/27 17:38:18 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(char **args, t_data *data)
{
	char	*path;
	int		lenght;

	(void)args;
	(void)data;
	path = getcwd(NULL, 0);
	if (!path)
		return (ft_error());
	lenght = ft_strlen(path);
	if (write(STDOUT_FILENO, path, lenght) != lenght)
	{
		free(path);
		return (ft_error());
	}
	free(path);
	if (write(STDOUT_FILENO, "\n", 1) != 1)
		return (ft_error());
	return (0);
}
