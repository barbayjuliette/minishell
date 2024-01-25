/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:54:06 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/25 14:21:03 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_tilde(char **value)
{
	int		i;
	char	*str;


	i = 0;
	str = *value;
	ft_strchr(str, 126);
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}

}

void	expand_all(t_token *token)
{
	while (token)
	{
		expand_tilde(&(token->value));
		token = token->next;
	}
}
