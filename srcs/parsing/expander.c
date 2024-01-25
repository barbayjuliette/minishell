/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:54:06 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/25 21:44:27 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Environment variable cannot start with a digit
// Only uppercase, lowercase, and underscores are allowed for environment variables
// Not used here anymore. We only need to check if variable is valid during export, not when using it.
// I leave it so you can use it at execution.

int	var_is_valid(char c, int i)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	get_variable_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && var_is_valid(str[i], i))
		i++;
	return (i);
}

char	*get_variable(char *str, int *i, int len)
{
	char	*var;
	char	*value;
	char	*prefix;
	char	*suffix;
	char	*join;

	prefix = ft_substr(str, 0, *i);
	var = ft_substr(str + *i + 1, 0, len);
	value = getenv(var);
	free(var);
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

// TEST: thisis$USER"xest"$USER

char	*get_var_double(char *str, int *i)
{
	int	len;

	(*i)++;
	while (str[*i] && str[*i] != 34)
	{
		if (str[*i] == '$')
		{
			len = get_variable_len(str + *i + 1);
			str = get_variable(str, i, len);
		}
		(*i)++;
	}
	return (str);
}

// Test: test"hello"$USER

void	expand_variables(char **value)
{
	int		i;
	char	*str;
	int		len;

	i = 0;
	str = *value;
	while (str[i])
	{
		if (str[i] == 39)
			i += find_index(str + i + 1, 39);
		else if (str[i] == 34)
			str = get_var_double(str, &i);
		else if (str[i] == '$')
		{
			len = get_variable_len(str + i + 1);
			str = get_variable(str, &i, len);
		}
		i++;
	}
	*value = str;
}

void	expand_all(t_token *token)
{
	while (token)
	{
		expand_variables(&(token->value));
		token = token->next;
	}
}
