/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:59:45 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/24 14:38:18 by jbarbay          ###   ########.fr       */
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

int	get_cmds(t_token *token, t_cmd_table **table)
{
	int		i;
	t_token	*start;
	char	**cmd;

	i = 0;
	start = token;
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
	token = start;
	cmd = (char **)malloc(sizeof(char *) * (i + 1));
	// Add malloc error
	token = start;
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

t_cmd_table	*parsing(t_token *token, t_cmd_table **table)
{
	t_cmd_table *new;

	if (token->type == PIPE)
	{
		printf("Persing error");
		return (NULL);
	}
	new = init_pipeline();
	get_redirections(token, &new);
	get_cmds(token, &new);

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
