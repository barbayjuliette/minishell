/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:54:06 by jbarbay           #+#    #+#             */
/*   Updated: 2024/03/12 17:32:56 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
extern int	g_status;

// Environment variable cannot start with a digit
// Only uppercase, lowercase, digits and underscores are allowed for env var.
// We only need to show error message if not valid during export, not when using it.

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
		value = ft_itoa(g_status);
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

// TEST: thisis$USER"xest"$USER
// Replace 127 with exit status
// if (str[*i] == '$' && str[*i + 1] && str[*i + 1] != ' ' && str[*i + 1] != 34)

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

// Test: test"hello"$USER

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
		else if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
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
		expand_variables(&(token->value),data);
		remove_quotes(&(token->value));
		token = token->next;
	}
}

void	remove_empty_tokens(t_token **token)
{
	t_token	*current;
	t_token	*next;

	current = *token;
	if (current && ft_strlen(current->value) == 0)
	{
		*token = (*token)->next;
		free(current->value);
		current->value = NULL;
		free(current);
	}
	current = *token;
	while (current)
	{
		next = current->next;
		if (next && ft_strlen(next->value) == 0)
		{
			free(next->value);
			next->value = NULL;
			current->next = next->next;
			free(next);
		}
		current = current->next;
	}
}

// Invalid first character of environment vraiable, or variable not found
// -> replace with empty string

// There are many different ways bash handles $ when the characters following $
// are invalid.
// So I simplified it.

// echo $,TEST --> $,TEST
// echo $*TEST --> TEST
// echo $9TEST --> TEST

// I handled it as :
// If the first character after the $ is invalid,
// I replace the $9 with an empty string, like echo $9TEST --> TEST
// To get the variable name. I get the characters, as long as they are valid.
// Once the char is invalid, I stop adding it as the variable name.
// echo $USER%TEST--> Varibale name is USER.
// Bash : echo $USER% --> juliettebarbay%

// If I have "This costs 45$" or "This costs $ 45"
// Output is the same, $ is not a variable there
