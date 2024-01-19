/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:15:31 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/19 17:20:53 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Anything else will be WORD
// cmd1|cmd2>outfile will work, recognizes the pipe and redirections
// Something like $VAR could be stored as WORD, so some values inside WORD might need to get expanded
// Example: p$VAR -> during execution expanded as pwd
// Examples: echo"hel  lo""hello"  OR echo"hello'hello" : one single token
// "echo" or "e"ch""o -> works as echo
// echo "ftyf" gjyfvgu ech"gcjty " ioh|
// "e"ch""o : SHOULD BE ONE SINGLE token
// "p""w""d": one token, works as pwd

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
// We can have quotes inside word
// Example echo"hello""hello" -> cmd not found echohellohello
// Make sure the quotes are closed
// pwd'd' -> valid, pw'd -> not valid
// echo"hello'hi" -> valid as a token, echo"hello -> invalid token

int	process_string(char **line, t_token **list)
{
	int		i;
	char	*str;
	int		pos;

	i = 0;
	while ((*line)[i] && (*line)[i] != '|' && (*line)[i] != '<' && (*line)[i] != '>' && !ft_strchr(WHITESPACE, (*line)[i]))
	{
		if ((*line)[i] == 34 || (*line)[i] == 39 )
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
	create_token(WORD, str, list);
	*line += i;
	return (0);
}
