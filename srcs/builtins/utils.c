/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:05:22 by akolgano          #+#    #+#             */
/*   Updated: 2024/02/27 14:05:24 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error(void)
{
	write(1, "Error\n", 6);
	return (-1);
}

int	ft_strcontains(const char *s, const char c)
{
	if (s)
	{
		while (*s && *s != c)
			++s;
		if (*s == c)
			return (1);
	}
	return (0);
}

int	ft_compare(char *str, char *var)
{
	int	i;
	int	j;

	j = ft_strlen(str);
	i = 0;
	while (i < j && str[i] != '=')
	{
		if (str[i] != var[i])
			return (1);
		i++;
	}
	if (var[i] == '=')
		return (0);
	return (1);
}

int	print_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		ft_putendl_fd(data->envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

int	var_is_valid(char *line)
{
	int	i;

	i = 0;
	if (ft_isdigit(line[i]))
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd(line, STDERR_FILENO);
		ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
		return (-1);
	}
	while (line[i] && !ft_strchr(WSPACE, line[i]) \
		&& !is_id(line[i]))
	{
		if (!ft_isalnum(line[i]) && line[i] != '_')
		{
			ft_putstr_fd("export: ", STDERR_FILENO);
			ft_putstr_fd(line, STDERR_FILENO);
			ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
			return (-1);
		}
		i++;
	}
	return (i);
}
