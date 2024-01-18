/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:32:31 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/18 13:15:21 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Read line
// Exit when type exit
// History

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
	char	*line;
	t_token	*tokens;

	while (1)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		if (is_exit(line))
			break ;
		tokens = get_tokens(line);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		// print_tokens(tokens);
		free_tokens(&tokens);
		free(line);
	}
	// rl_clear_history();
	return (0);
}
