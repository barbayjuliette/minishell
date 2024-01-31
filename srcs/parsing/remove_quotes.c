/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:40:27 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/31 15:15:51 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*update_string_quotes(char *str, int *i, int c)
{
	char	*prefix;
	char	*suffix;
	char	*join;
	char	*unquoted;
	int		second_quote;

	prefix = ft_substr(str, 0, *i);
	second_quote = find_index(str + *i + 1, c) + *i + 1;
	unquoted = ft_substr(str, *i + 1, second_quote - (*i + 1));
	suffix = ft_substr(str, second_quote + 1, ft_strlen(str) - second_quote);
	free(str);
	join = ft_strjoin(prefix, unquoted);
	str = ft_strjoin(join, suffix);
	free(join);
	free(prefix);
	free(suffix);
	free(unquoted);
	(*i) = second_quote - 2;
	return (str);
}

void	remove_quotes(char **value)
{
	int		i;
	char	*str;

	i = 0;
	str = *value;
	while (str[i])
	{
		if (str[i] == 39)
			str = update_string_quotes(str, &i, 39);
		else if (str[i] == 34)
			str = update_string_quotes(str, &i, 34);
		i++;
	}
	*value = str;
}
