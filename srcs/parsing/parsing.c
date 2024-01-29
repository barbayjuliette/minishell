/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:59:45 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/29 17:26:14 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_table	*init_pipeline(void)
{
	t_cmd_table	*new;

	new = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	if (!new)
		return (NULL);
	new->cmds = NULL;
	new->input = NULL;
	new->output = NULL;
	new->next = NULL;
	return (new);
}

// First I add all the redirections to the pipeline
// Redirection must be followed by identifer

int	get_redirections(t_token *token, t_cmd_table **table)
{
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == REDIR_IN_SINGLE || token->type == REDIR_IN_DOUBLE)
		{
			if (!token->next || token->next->type != IDENTIFIER)
				return (1);
			create_token(token->type, token->next->value, &((*table)->input));
			token = token->next;
		}
		else if (token->type == REDIR_OUT_SINGLE || token->type == REDIR_OUT_DOUBLE)
		{
			if (!token->next || token->next->type != IDENTIFIER)
				return (1);
			create_token(token->type, token->next->value, &((*table)->output));
			token = token->next;
		}
		token = token->next;
	}
	return (0);
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
		if (token->type == IDENTIFIER)
			i++;
		token = token-> next;
	}
	return (i);
}

// Then I add all the commands, but I have to skip the redirections + the identifier following the redirection
int	get_cmds(t_token *token, t_cmd_table **table)
{
	int		i;
	char	**cmd;

	i = get_length_cmd(token);
	cmd = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (0);
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

// I cannot start or finish the prompt with a pipe.
// I create a new pipeline then add it to the back of the linked list
// I add the redirections then the commands to the pipeline
// Then I update the token to get to the end of the pipeline and process the next one if there is one.

t_cmd_table	*parsing(t_token *token, t_cmd_table **table)
{
	t_cmd_table	*new;
	t_cmd_table	*list;
	t_token		*first_token;

	list = NULL;
	first_token = token;
	if (!token || token->type == PIPE)
		return (NULL);
	while (token)
	{
		if (token->type == PIPE && !token->next)
			return (error_parsing(1, &list, &first_token));
		if (token->type == PIPE)
			token = token->next;
		new = init_pipeline();
		if (!new)
			return (error_parsing(2, &list, &first_token));
		ft_cmds_add_back(&list, new);
		if (get_redirections(token, &new))
			return (error_parsing(1, &list, &first_token));
		if (!get_cmds(token, &new))
			return (error_parsing(2, &list, &first_token));
		token = update_token(token);
	}
	// print_all_commands(list);
	return (list);
}
