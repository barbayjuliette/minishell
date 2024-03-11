/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:26:41 by akolgano          #+#    #+#             */
/*   Updated: 2024/02/27 17:26:43 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	find_env_var(t_data *data, char *var)
{
	int	i;

	i = 0;
	while (data->envp[i] != NULL)
	{
		if (ft_compare(var, data->envp[i]) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

void	free_env_var(char *var)
{
	free(var);
}

void	remove_env_var(t_data *data, int pos)
{
	while (data->envp[pos] != NULL)
	{
		data->envp[pos] = data->envp[pos + 1];
		pos++;
	}
}

int	ft_unset(char **args, t_data *data)
{
	int	pos;

	if (args[1] == NULL)
		return (1);
	pos = find_env_var(data, args[1]);
	if (pos != -1)
	{
		remove_env_var(data, pos);
		return (0);
	}
	else
		return (1);
}
