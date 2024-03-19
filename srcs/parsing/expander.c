/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:54:06 by jbarbay           #+#    #+#             */
/*   Updated: 2024/03/19 11:32:01 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*update_string(char *str, int *i, int len, char *value)
{
	char	*prefix;
	char	*suffix;
	char	*join;

	prefix = ft_substr(str, 0, *i);
	suffix = ft_substr(str, len + *i + 1, ft_strlen(str) - len - *i - 1);
	join = ft_strjoin(prefix, value);
	free(str);
	str = ft_strjoin(join, suffix);
	free(prefix);
	free(suffix);
	free(join);
	*i += (ft_strlen(value) - 1);
	return (str);
}

char	*get_variable(char *str, int *i, int len, t_data *data)
{
	char	*value;

	if (str[*i + 1] && str[*i + 1] == '?')
	{
		len = 1;
		value = ft_itoa(data->exit_code);
	}
	else if (len == 0)
	{
		value = ft_strdup("");
		len = 1;
	}
	else
		value = get_value_variable(str, *i, len, data);
	str = update_string(str, i, len, value);
	free(value);
	return (str);
}

char	*find_variable_quotes(char *str, int *i, t_data *data)
{
	int	len;

	(*i)++;
	while (str[*i] && str[*i] != 34)
	{
		if (str[*i] == '$' && str[*i + 1]
			&& !ft_strchr(WSPACE, str[*i + 1]) && str[*i + 1] != 34)
		{
			len = get_variable_len(str + *i + 1);
			str = get_variable(str, i, len, data);
		}
		(*i)++;
	}
	return (str);
}

void	expand_variables(char **value, t_data *data)
{
	int		i;
	char	*str;
	int		len;

	i = 0;
	str = *value;
	while (str[i])
	{
		if (str[i] == 39)
			i += (find_index(str + i + 1, 39) + 1);
		else if (str[i] == 34)
			str = find_variable_quotes(str, &i, data);
		else if (str[i] == '$' && str[i + 1] && !ft_strchr(WSPACE, str[i + 1]))
		{
			len = get_variable_len(str + i + 1);
			str = get_variable(str, &i, len, data);
		}
		i++;
	}
	*value = str;
}

void	expand_all(t_token *token, t_data *data)
{
	while (token)
	{
		expand_variables(&(token->value), data);
		remove_quotes(&(token->value));
		token = token->next;
	}
}
