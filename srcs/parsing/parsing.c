/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:59:45 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/24 16:21:58 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_table	*init_pipeline(void)
{
	t_cmd_table *new;

	new = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	new->cmds = NULL;
	new->input = NULL;
	new->output = NULL;
	new->next = NULL;
	return (new);
}

// Redirection must be followed by identifer
int	get_redirections(t_token *token, t_cmd_table **table)
{
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == REDIR_IN_SINGLE  || token->type == REDIR_IN_DOUBLE)
		{
			if (!token->next || token->next->type != IDENTIFIER)
			{
				printf("Parsing error\n");
				return (-1);
			}
			create_token(token->type, token->next->value, &((*table)->input));
			token = token->next;
		}
		else if (token->type == REDIR_OUT_SINGLE  || token->type == REDIR_OUT_DOUBLE)
		{
			if (!token->next || token->next->type != IDENTIFIER)
			{
				printf("Parsing error\n");
				return (-1);
			}
			create_token(token->type, token->next->value, &((*table)->output));
			token = token->next;
		}
		token = token->next;
	}
	return (1);
}

int	get_length_cmd(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type > 2)
		{
			token = token->next->next;
			continue ;
		}
		if (token->type == IDENTIFIER )
			i++;
		token = token-> next;
	}
	return (i);
}

int	get_cmds(t_token *token, t_cmd_table **table)
{
	int		i;
	char	**cmd;

	i = get_length_cmd(token);
	cmd = (char **)malloc(sizeof(char *) * (i + 1));
	// Add malloc error
	i = 0;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type > 2)
		{
			token = token->next->next;
			continue ;
		}
		cmd[i] = token->value;
		token = token->next;
		i++;
	}
	cmd[i] = NULL;
	(*table)->cmds = cmd;
	return (1);
}

t_token	*update_token(t_token *token)
{
	token = token->next;
	while (token && token->type != PIPE)
		token = token->next;
	return (token);
}

t_cmd_table	*parsing(t_token *token, t_cmd_table **table)
{
	t_cmd_table *new;
	t_cmd_table *list;

	list = NULL;
	if (token->type == PIPE)
	{
		printf("Parsing error\n");
		return (NULL);
	}
	while (token)
	{
		if (token->type == PIPE && !token->next)
		{
			printf("Parsing error\n");
			return (NULL);
		}
		if (token->type == PIPE)
			token = token->next;
		new = init_pipeline();
		ft_cmds_add_back(&list, new);
		get_redirections(token, &new);
		get_cmds(token, &new);
		token = update_token(token);
	}
	print_all_commands(list);
	return (new);
}

void	print_all_commands(t_cmd_table *table)
{
	while (table)
	{
		print_command_table(table);
		table = table->next;
		printf("\n");
	}
}

void	print_command_table(t_cmd_table *table)
{
	int	i;

	i = 0;
	printf("Commands: ");
	while (table->cmds[i])
	{
		printf("%s ", table->cmds[i]);
		i++;
	}
	printf("\n");
	printf("INPUT:\n");
	print_tokens(table->input);
	printf("OUTPUT:\n");
	print_tokens(table->output);
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
