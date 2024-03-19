/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_names.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:36:19 by akolgano          #+#    #+#             */
/*   Updated: 2024/03/14 12:36:20 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include <assert.h>

int	add_new_name(char *name, int length, t_data *data)
{
	char	**tmp_env;

	tmp_env = (char **)malloc(sizeof(char *) * (length + 2));
	if (!tmp_env)
	{
		free(name);
		return (1);
	}
	add_new_name_02(name, tmp_env, 0, data);
	if (data->ptr_allocated_by_program != -1)
		free(data->envp);
	data->envp = tmp_env;
	return (0);
}

void	add_new_name_02(char *name, char **tmp_env, int i, t_data *data)
{
	char	flag;
	int		j;

	j = 0;
	flag = 1;
	while (data->envp[i])
	{
		if (name[0] <= data->envp[i][0] && flag)
		{
			tmp_env[j] = name;
			flag = 0;
			j++;
		}
		else
		{
			tmp_env[j] = data->envp[i];
			i++;
			j++;
		}
	}
	if (flag)
		tmp_env[j++] = name;
	tmp_env[j] = NULL;
}

void	change_name(char *name, char *tmp_name, int i, t_data *data)
{
	int	length;

	length = 0;
	while (name[length] != '=' && name[length])
		length++;
	if (name[length])
		data->envp[i] = tmp_name;
}

int	find_name(char *name, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->envp[i])
	{
		j = 0;
		while (name[j] && name[j] != '=' && name[j] != '+' && \
				name[j] == data->envp[i][j])
			j++;
		if ((!name[j] || name[j] == '=' || name[j] == '+') && \
			(data->envp[i][j] == '=' || !data->envp[i][j]))
			return (i);
		i++;
	}
	return (i);
}

int	find_value(int i, t_data *data)
{
	int	j;

	j = 0;
	while (data->envp[i][j] != '=' && data->envp[i][j])
		j++;
	if (data->envp[i][j] == '=')
		return (++j);
	else
		return (j);
}
