/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:32:45 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/17 21:43:18 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*get_tokens(char *line)
{
	int	i;
	t_token *list;

	i = 0;
	list = NULL;
	while (line[i])
	{
		if (ft_strchr(WHITESPACE, line[i]))
			i++;

		else if (line[i] == '|')
		{
			create_token(PIPE, "|", &list);
			printf("This is a pipe\n");
			i++;
		}
		else
		{
			i++;
		}
	}
	return (list);
}

void	create_token(int type, char *str, t_token **list)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	// if (!new)
	// 	return (NULL);
	new->type = type;
	new->value = ft_strdup(str);
	new->next = NULL;
	printf("adding tokens\n");
	ft_token_add_back(list, new);
	printf("About to print 2\n");
}

void	ft_token_add_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (*lst == NULL)
	{
		printf("FIRST OF THE LIST \n");
		*lst = new;
		return ;
	}
	temp = *lst; // problem is here
	while (temp->next)
	{
		temp = temp->next;
	}
	printf("LATER ON THE LIST \n");
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
