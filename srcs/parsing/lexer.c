/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:32:45 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/19 17:45:43 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// I find the quote that will close it. If I don't find it, I will return an error

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

// I first check if the environment viariable has a valid syntax

int	process_env_var(char **line, t_token **list)
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

// I find > / <. i check if the char after is the same char to know if single or double.
int	process_redirect(char **line, char *c, t_token **list)
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
			if (process_env_var(&line, &list) == -1)
				return (NULL);
		}
		else if (*line == '<')
			line += process_redirect(&line, "<", &list);
		else if (*line == '>')
			line += process_redirect(&line, ">", &list);
		else if (*line == '|')
			line += process_pipe(&list);
		else
			if (process_string(&line, &list) == -1)
				return (NULL);
	}
	return (list);
}