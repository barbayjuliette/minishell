/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:54:06 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/26 16:07:24 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Environment variable cannot start with a digit
// Only uppercase, lowercase, digits and underscores are allowed for environment variables
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
	{
		if (i == 0 && ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (i);
}

char	*get_value_variable(char *str, int i, int len)
{
	char	*var;
	char	*value;

	var = ft_substr(str + i + 1, 0, len);
	value = getenv(var);
	if (!value)
		value = "";
	free(var);
	return (value);
}

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

char	*get_variable(char *str, int *i, int len, int exit_status)
{
	char	*value;
	char	*val;
	int		malloced; // Tells us if value was malloced and will need to be freed

	malloced = 0;
	if (str[*i + 1] && str[*i + 1] == '?')
	{
		len = 1;
		value = ft_itoa(exit_status); // Malloced string
		malloced = 1;
	}
	else if (len == 0)
	{
		value = "";
		len = 1;
	}
	else
		value = get_value_variable(str, *i, len);
	str = update_string(str, i, len, value);
	if (malloced)
		free(value);
	return (str);
}

// TEST: thisis$USER"xest"$USER
// Replace 127 with exit status

char	*get_var_double(char *str, int *i)
{
	int	len;

	(*i)++;
	while (str[*i] && str[*i] != 34)
	{
		if (str[*i] == '$' && str[*i + 1] && str[*i + 1] != ' ' && str[*i + 1] != 34)
		{
			len = get_variable_len(str + *i + 1);
			str = get_variable(str, i, len, 127);
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
		else if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			len = get_variable_len(str + i + 1);
			str = get_variable(str, &i, len, 127);
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

// Invalid first character of environment vraiable, or variable not found -> replace with empty string

// There are many different ways bash handles $ when the characters following $ are invalid.
// So I simplified it.

// echo $,TEST --> $,TEST
// echo $*TEST --> TEST
// echo $9TEST --> TEST

// I handled it as :
// If the first character after the $ is invalid, I replace the $9 with an empty string, like echo $9TEST --> TEST
// To get the variable name. I get the characters, as long as they are valid. Once the char is invalid, I stop adding it as the variable name.
// echo $USER%TEST--> Varibale name is USER.
// Bash : echo $USER% --> juliettebarbay%

// If I have "This costs 45$" or "This costs $ 45"
// Output is the same, $ is not a variable there
