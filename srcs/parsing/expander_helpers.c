/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:41:46 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/26 22:42:07 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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