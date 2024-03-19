/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:41:46 by jbarbay           #+#    #+#             */
/*   Updated: 2024/03/19 11:13:29 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	var_is_valid_exp(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	get_variable_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_strchr(WSPACE, str[i]) && var_is_valid_exp(str[i]))
	{
		if (i == 0 && ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (i);
}

char	*get_value_variable(char *str, int i, int len, t_data *data)
{
	char	*var;
	char	*value;

	var = ft_substr(str + i + 1, 0, len);
	value = ft_getenv(var, data);
	if (!value)
		value = "";
	free(var);
	return (value);
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
