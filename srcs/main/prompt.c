/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:32:31 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/25 14:09:17 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Read line
// Exit when type exit
// Add to history (except if the line is empty)
// Create tokens based on the input
// If tokens is NULL, it means there was an error (with message): new prompt

#include "../../includes/minishell.h"

int	is_exit(char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, WHITESPACE);
	if (ft_strncmp(trimmed, "exit", 5) == 0)
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	return (0);
}

int main(void)
{
	char		*line;
	t_token		*tokens;
	t_cmd_table	*table;

	while (1)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		if (is_exit(line))
		{
			free(line);
			break ;
		}
		tokens = get_tokens(line);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		// print_tokens(tokens);
		expand_all(tokens);
		table = parsing(tokens, &table);
		if (!table)
		{
			free(line);
			continue ;
		}
		print_all_commands(table);
		free_tokens(&tokens, 1);
		free_commands(&table);
		free(line);
	}
	// rl_clear_history();
	return (0);
}
