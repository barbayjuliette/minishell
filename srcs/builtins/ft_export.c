/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:02:32 by akolgano          #+#    #+#             */
/*   Updated: 2024/03/13 14:19:36 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char *name, t_data *data)
{
	int		i;
	char	*env_name;

	i = 0;
	while (data->envp[i])
	{
		env_name = get_name(data->envp[i]);
		if (ft_compare1(name, env_name) == 0)
		{
			free(env_name);
			return (get_value(data->envp[i]));
		}
		else
			i++;
		free(env_name);
	}
	return (ft_strdup(""));
}

char	*ft_getenv_for_env(char *name, t_data *data)
{
	int		i;
	char	*env_name;

	i = 0;
	while (data->envp[i])
	{
		env_name = get_name(data->envp[i]);
		if (ft_compare1(name, env_name) == 0)
		{
			free(env_name);
			return (get_value(data->envp[i]));
		}
		else
			i++;
		free(env_name);
	}
	return (0);
}

int	check_name_02(char *name, char flag, int i)
{
	while (name[i] && name[i] != '=' && name[i] != '+')
	{
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	if (flag == 3 && name[i] == '+')
	{
		i++;
		if (name[i] != '=')
			return (0);
		return (10);
	}
	if (name[i] != '=')
		return (5);
	return (1);
}

int	check_name(char *name, char flag)
{
	int	i;

	i = 1;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	if (flag)
		return (check_name_02(name, flag, i));
	else
	{
		while (name[i])
		{
			if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_')
				return (0);
			i++;
		}
	}
	return (1);
}

int	ft_export(char **argv, t_data *data)
{
	int	i;
	int	flag;

	i = 1;
	if (!argv[i])
		return (print_env(data));
	while (argv[i])
	{
		flag = check_name(argv[i], 3);
		if (flag)
		{
			add_var_evp(argv[i], flag, data);
		}
		else
		{
			ft_putstr_fd("export: ", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
			data->exit_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
