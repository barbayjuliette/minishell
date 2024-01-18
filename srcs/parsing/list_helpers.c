/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:27:04 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/18 16:27:22 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_token(int type, char *str, t_token **list)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	// if (!new)
	// 	return (NULL);
	new->type = type;
	new->value = str;
	new->next = NULL;
	ft_token_add_back(list, new);
}

void	ft_token_add_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
}

void	print_tokens(t_token *token)
{
	int	i;

	i = 0;
	printf("Printing TOKENS: \n");
	while (token)
	{
		printf("Item %d:, type: %d, value: %s\n", i, token->type, token->value);
		i++;
		token = token->next;
	}
}

void	free_tokens(t_token **list)
{
	t_token	*current;
	t_token	*next;

	current = *list;
	while (current)
	{
		next = current->next;
		free(current->value);
		current->value = NULL;
		free(current);
		current = next;
	}
	*list = NULL;
}