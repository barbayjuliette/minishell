/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:32:45 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/18 19:01:11 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_quote(char **line, int quote, t_token **list)
{
	int		i;
	char	*str;

	i = 1;
	if (!ft_strchr(*line + 1, quote))
		error_tokens(3, list);
	while ((*line + i) && *(*line + i) != quote)
		i++;
	i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	ft_strlcpy(str, *line, i + 1);
	if (quote == 34)
		create_token(DOUBLE, str, list);
	else
		create_token(SINGLE, str, list);
	*line += i;
	return (i);
}

int	error_tokens(int error, t_token **list)
{
	if (error == 1)
		printf("Environment variable cannot start with a digit\n");
	else if (error == 2)
		printf("Only uppercase, lowercase, and underscores are allowed for environment variables\n");
	else if (error == 3)
		printf("Syntax error: unclosed quotes\n");
	free_tokens(list);
	return (-1);
}

int	process_variable(char **line, t_token **list)
{
	int		i;
	char	*str;

	i = 1;
	if (ft_isdigit((*line)[i]))
		return (error_tokens(1, list));
	while (*line + i && !ft_strchr(WHITESPACE, (*line)[i]))
	{
		if (!ft_isalnum((*line)[i]) && (*line)[i] != '_')
			return (error_tokens(2, list));
		i++;
	}
	str = (char *)malloc(sizeof(char) * (i + 1));
	ft_strlcpy(str, *line, i + 1);
	create_token(ENV_VAR, str, list);
	*line += i;
	return (i);
}

int	process_pipe(t_token **list)
{
	char	*str;

	str = ft_strdup("|");
	create_token(PIPE, str, list);
	return (1);
}

int	process_input(char **line, char *c, t_token **list)
{
	char	*str;

	if (ft_strncmp((*line + 1), c, 1) == 0)
	{
		str = ft_strjoin((char *)c, (char *)c);
		if (c[0] == '<')
			create_token(REDIR_IN_DOUBLE, str, list);
		else
			create_token(REDIR_OUT_DOUBLE, str, list);
		return (2);
	}
	else
	{
		str = ft_strdup((char *)c);
		if (c[0] == '<')
			create_token(REDIR_IN_SINGLE, str, list);
		else
			create_token(REDIR_OUT_SINGLE, str, list);
		return (1);
	}
}

// We can have quotes inside string
// Example echo"hello""hello" -> cmd not found echohellohello
// Make sure the quotes are closed
// pwd'd' -> valid, pw'd -> not valid
// echo"hello'hi" -> valid as a token, echo"hello -> invalid token

int	find_quote(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (0);
}

int	check_unclosed_quotes(char *str, t_token **list)
{
	int	i;
	int	pos;

	i = 1;
	while (str[i])
	{
		//  If we find the quote, we have to find the second one
		if (str[i] == 34)
		{
			pos = find_quote(str + i + 1, 34);
			if (!pos)
				return (error_tokens(3, list));
			else
				i += pos;
		}
		else if (str[i] == 39)
		{
			pos = find_quote(str + i + 1, 39);
			if (!pos)
				return (error_tokens(3, list));
			else
				i += pos;
		}
		else
			i++;
	}
	return (i);
}

// Anything else will be STRING
// cmd1|cmd2>outfile will work, recognizes the pipe and redirections
// Something like $VAR could be stored as STRING, so some values inside STRING might need to get expanded
// Example: p$VAR -> during execution expanded as pwd

int	process_string(char **line, t_token **list)
{
	int		i;
	char	*str;

	i = 0;
	while ((*line)[i] && (*line)[i] != '|' && (*line)[i] != '<' && (*line)[i] != '>')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	ft_strlcpy(str, *line, i + 1);
	create_token(STRING, str, list);
	if (check_unclosed_quotes(str, list) == -1)
		return (-1);
	*line += i;
	return (0);
}

t_token	*get_tokens(char *line)
{
	t_token	*list;

	list = NULL;
	while (*line)
	{
		if (ft_strchr(WHITESPACE, *line))
			line++;
		else if (*line == 34)
		{
			if ((process_quote(&line, 34, &list)) == -1)
				return (NULL);
		}
		else if (*line == 39)
		{
			if (process_quote(&line, 39, &list) == -1)
				return (NULL);
		}
		else if (*line == '$')
		{
			if (process_variable(&line, &list) == -1)
				return (NULL);
		}
		else if (*line == '<')
			line += process_input(&line, "<", &list);
		else if (*line == '>')
			line += process_input(&line, ">", &list);
		else if (*line == '|')
			line += process_pipe(&list);
		else
			if (process_string(&line, &list) == -1)
				return (NULL);
	}
	return (list);
}
