/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:32:31 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/15 22:38:57 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Read line
// Exit when type exit
// History

#include "../../includes/minishell.h"

int main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		if (ft_strncmp(ft_strtrim(line, WHITESPACE), "exit", 5) == 0)
			break;
		free(line);
	}
	// rl_clear_history();
	return (0);
}
