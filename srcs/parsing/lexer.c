/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:32:45 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/17 18:49:24 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*get_tokens(char *line)
{
	int	i;
	t_token *tokens;

	i = 0;
	tokens = NULL;
	while (line[i])
	{
		if (ft_strchr(WHITESPACE, line[i]))
			i++;
		
		else if (line[i] == '|')
		{
			create_token(PIPE, line, tokens);
			printf("This is a pipe\n");
			i++;
		}
		else 
		{
			printf("HERE\n");
			i++;
		}
	}
	if (tokens)
	{
		printf("About to print\n");
		printf("Token: %d\n", tokens->type);
		print_tokens(tokens);
	}
	else
	{ 
		printf("no tokens found\n");
	}
	return (NULL);
}

void	create_token(int type, char *str, t_token *list)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	// if (!new)
	// 	return (NULL);
	new->type = type;
	new->value = ft_strdup(str);
	new->next = NULL;
	printf("adding tokens\n");
	ft_token_add_back(&list, new); // Problem is here
}

void	ft_token_add_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	printf("HERE98\n");
	if (lst == NULL)
	{
		printf("HERE3\n");
		lst = &new;
		printf("HERE999999\n");
		return ;
	}
	temp = *lst; // problem is here 
	printf("HERE22222\n");
	while (temp->next)
	{
		printf("HERE6\n");
		temp = temp->next;
	}
	temp->next = new;
	printf("HERE5\n");
}

void	print_tokens(t_token *token)
{
	int	i;

	i = 0;
	printf("Printing tokens\n");
	while (token)
	{
		printf("Item %d:, type: %d, value: %s", i, token->type, token->value);
		i++;
		token = token->next;
	}
}