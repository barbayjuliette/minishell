/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:37:47 by akolgano          #+#    #+#             */
/*   Updated: 2024/03/11 12:37:49 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup2(const char *s1)
{
	int		len;
	int		i;
	char	*copy;
	char	*tmp;

	len = ft_strlen(s1);
	i = 0;
	copy = (char *)malloc(sizeof(char) * (len + 4));
	tmp = (char *)malloc(sizeof(char) * (len + 4));
	if (!copy)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	tmp = ft_strjoin(copy, "=''\0");
	free(copy);
	return (tmp);
}

char	*get_name(char *s)
{
	int		len_name;
	char	*env_name;
	char	*equal_sign_pos;

	equal_sign_pos = ft_strchr(s, '=');
	if (!equal_sign_pos)
		len_name = ft_strlen(s);
	else
		len_name = equal_sign_pos - s;
	env_name = (char *)malloc(len_name + 1);
	ft_strlcpy(env_name, s, len_name + 1);
	return (env_name);
}

char	*get_value(char *s)
{
	char	*equal_sign_pos;
	char	*value;
	int		len_value;

	equal_sign_pos = ft_strchr(s, '=');
	if (!equal_sign_pos)
		return (NULL);
	len_value = ft_strlen(equal_sign_pos + 1);
	value = (char *)malloc(len_value + 1);
	ft_strlcpy(value, equal_sign_pos + 1, len_value + 1);
	return (value);
}

int	ft_compare1(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

void	handle_error_blocking(char **cmd, t_data *data)
{
	if (!ft_compare1(cmd[0], "wc"))
		ft_putendl_fd("	      0       0       0", 2);
	free(data->pipefds);
	free_tokens(&data->tokens, 1);
	free_commands(&data->tbl);
	exit(0);
}
