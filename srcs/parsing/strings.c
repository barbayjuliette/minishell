/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:15:31 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/19 20:24:56 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// Test cases:
// cmd1|cmd2>outfile -> cmd1, pipe, cmd2, >, outfile
// "This is a $VAR" -> We can have env_var inside identifiers
// echo"hel  lo""hello" OR echo"hello'hello" -> one single token
// "echo" or "e"ch""o -> works as echo, one single token
// "p""w""d" -> works as pwd, one single token
// echo"hello""hello" -> cmd not found echohellohello

int	find_index(const char *s, int c)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (0);
}

int	is_identifier(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

// If I find a quote, I make sure that they are closed. I make sure all the quotes are closed.

int	process_identifier(char **line, t_token **list)
{
	int		i;
	int		pos;
	char	*str;

	i = 0;
	while ( (*line)[i] && !is_identifier((*line)[i]) && !ft_strchr(WHITESPACE, (*line)[i]))
	{
		if ((*line)[i] == 34 || (*line)[i] == 39)
		{
			pos = find_index(*line + i, (*line)[i]);
			if (!pos)
				return (error_tokens(3, list));
			i += pos;
		}
		i++;
	}
	str = (char *)malloc(sizeof(char) * (i + 1));
	ft_strlcpy(str, *line, i + 1);
	create_token(IDENTIFIER, str, list);
	*line += i;
	return (i);
}
