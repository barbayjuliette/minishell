/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:27:04 by jbarbay           #+#    #+#             */
/*   Updated: 2024/03/19 11:07:58 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Create the new token and add it to the back of the list

int	create_token(int type, char *str, t_token **list)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (1);
	new->type = type;
	new->value = str;
	new->next = NULL;
	ft_token_add_back(list, new);
	return (0);
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

void	free_tokens(t_token **list, int i)
{
	t_token	*current;
	t_token	*next;

	current = *list;
	while (current)
	{
		next = current->next;
		if (i)
		{
			free(current->value);
			current->value = NULL;
		}
		free(current);
		current = next;
	}
	*list = NULL;
}

void	ft_cmds_add_back(t_cmd_table **lst, t_cmd_table *new)
{
	t_cmd_table	*temp;

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

void	free_commands(t_cmd_table **table)
{
	t_cmd_table	*current;
	t_cmd_table	*next;

	current = *table;
	while (current)
	{
		next = current->next;
		free(current->cmds);
		current->cmds = NULL;
		free_tokens(&(current->input), 0);
		current->input = NULL;
		free_tokens(&(current->output), 0);
		current->output = NULL;
		free(current);
		current = next;
	}
	*table = NULL;
}
