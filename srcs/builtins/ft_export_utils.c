/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:32:57 by akolgano          #+#    #+#             */
/*   Updated: 2024/03/14 12:32:58 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	add_value_02(char *name, int i, char *res, t_data *data)
{
	int	j;
	int	len;

	j = -1;
	len = 0;
	while (data->envp[i][++j])
		res[j] = data->envp[i][j];
	while (data->envp[i][len] != '=' && data->envp[i][len])
		len++;
	if (data->envp[i][len] != '=')
		res[j++] = '=';
	len = 0;
	while (name[len] != '=')
		len++;
	len++;
	while (name[len])
	{
		res[j] = name[len];
		len++;
		j++;
	}
	res[j] = '\0';
	if (data->envp[i])
		free(data->envp[i]);
	data->envp[i] = res;
}

void	add_value(char *name, int i, t_data *data)
{
	int		len;
	int		j;
	char	*res;

	j = 0;
	len = 0;
	len = ft_strlen(data->envp[i]);
	while (data->envp[i][j] != '=' && data->envp[i][j])
		j++;
	if (data->envp[i][j] != '=')
		len++;
	j = 0;
	while (name[j] != '=' && name[j])
		j++;
	j++;
	if (!name[j])
		return ;
	while (name[j++])
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return ;
	add_value_02(name, i, res, data);
}

void	add_var_evp(char *name, int flag, t_data *data)
{
	int		length;
	int		i;
	char	*tmp_name;

	length = 0;
	while (data->envp[length])
		length++;
	tmp_name = add_var_evp_02(name, flag, length, data);
	if (!tmp_name)
		return ;
	//if (data->tmp_name)
	//	free(data->tmp_name);	
	data->tmp_name = tmp_name;
	i = find_name(name, data);
	if (i == length)
		add_new_name(tmp_name, length, data);
	else
		change_name(name, tmp_name, i, data);
	data->ptr_allocated_by_program = i;
	//free(name);
}
char	*delete_plus(char *name)
{
	int		i;
	int		j;
	char	*res;

	i = ft_strlen(name);
	res = (char *)malloc(sizeof(char) * i);
	if (!res)
		return (res);
	i = 0;
	j = 0;
	while (name[i])
	{
		if (name[i] == '+')
			i++;
		else
		{
			res[j] = name[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
	return (res);
}
char	*add_var_evp_02(char *name, int flag, int length, t_data *data)
{
	char	*tmp_name;
	int		i;

	if (flag == 10)
	{
		i = find_name(name, data);
		if (i == length)
			tmp_name = delete_plus(name);
		else
		{
			add_value(name, i, data);
			return (NULL);
		}
	}
	else
	{
		i = find_name(name, data);
		tmp_name = ft_strdup(name);
	}
	return (tmp_name);
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
