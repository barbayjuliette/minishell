/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:08:45 by jbarbay           #+#    #+#             */
/*   Updated: 2024/03/11 12:04:51 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*update_token(t_token *token)
{
	token = token->next;
	while (token && token->type != PIPE)
		token = token->next;
	return (token);
}

t_cmd_table	*error_parsing(int i, t_cmd_table **list, t_token **tokens)
{
	if (i == 1)
		printf("Parsing error\n");
	else if (i == 2)
		printf("Malloc error\n");
	free_tokens(tokens, 1);
	free_commands(list);
	return ((t_cmd_table *) NULL);
}
