/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:59:45 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/23 18:09:01 by jbarbay          ###   ########.fr       */
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

t_cmd_table *parse_cmd(t_token *token, t_cmd_table **table)
{
	t_cmd_table *new;
	t_token		*start;
	char		**cmd;
	int			i;

	start = token;
	i = 0;
	new = init_pipeline();
	while (token != NULL && token->type == IDENTIFIER)
	{
		i++;
		token = token->next;
	}
	cmd = (char **)malloc(sizeof(char *) * (i + 1));
	token = start;
	i = 0;
	while (token != NULL && token->type == IDENTIFIER)
	{
		cmd[i] = token->value;
		token = token->next;
		i++;
	}
	cmd[i] = NULL;
	new->cmds = cmd;
	return (new);
}

// Redirection must be followed by identifer

int	get_redirections(t_token *token, t_cmd_table **table)
{
	while (token != NULL && token->type == IDENTIFIER)
		token = token->next;
	
	while (token != NULL && token->type != PIPE && token->type != IDENTIFIER)
	{
		if (!token->next || token->next->type != IDENTIFIER)
		{
			printf("error\n");
			return (-1);
		}
		if (token->type == REDIR_IN_SINGLE  || token->type == REDIR_IN_DOUBLE)
			create_token(token->type, token->next->value, &((*table)->input));
		if (token->type == REDIR_OUT_SINGLE || token->type == REDIR_OUT_DOUBLE)
			create_token(token->type, token->next->value, &((*table)->output));
		token = token->next->next;
	}
	// if (token->type == IDENTIFIER)
	// {
	// 	printf("HERE\n");
	// 	return (-1);
	// }
	return (1);
}

t_cmd_table	*parsing(t_token *token, t_cmd_table **table)
{
	t_cmd_table *new;

	if (token->type == IDENTIFIER)
	{
		new = parse_cmd(token, table);
		get_redirections(token, &new);
	}
	print_command_table(new);
	return (new);
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