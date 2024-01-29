/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:32:45 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/29 13:10:38 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// If tehre is an error, I print the error message and free the list

int	error_tokens(int error, t_token **list)
{
	if (error == 1)
		printf("Syntax error: unclosed quotes\n");
	else if (error == 2)
		printf("Malloc error\n");
	free_tokens(list, 1);
	return (1);
}

// Environment variable cannot start with a digit
// Only uppercase, lowercase, digits, and underscores are allowed for environment variables
// Not used here anymore. We only need to check if variable is valid during export, not when using it.
// I leave it so you can use it at execution.

int	env_var_is_valid(char *line)
{
	int	i;

	i = 1;
	if (ft_isdigit(line[i]))
		return (-1);
	while (line[i] && !ft_strchr(WHITESPACE, line[i]) && !is_identifier(line[i]))
	{
		if (!ft_isalnum(line[i]) && line[i] != '_')
			return (-1);
		i++;
	}
	return (i);
}

int	process_pipe(char **line, t_token **list)
{
	char	*str;

	str = ft_strdup("|");
	if (!str)
		return (error_tokens(2, list));
	if (create_token(PIPE, str, list))
		return (error_tokens(2, list));
	*line += 1;
	return (0);
}

int	process_redirect_1(char **line, t_token **list)
{
	int		error;
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (error_tokens(2, list));
	ft_strlcpy(str, *line, 2);
	if (*line[0] == '<')
		error = create_token(REDIR_IN_SINGLE, str, list);
	else
		error = create_token(REDIR_OUT_SINGLE, str, list);
	if (error)
		return (error_tokens(2, list));
	*line += 1;
	return (0);
}

int	process_redirect_2(char **line, t_token **list)
{
	char	*str;
	int		error;

	str = malloc(sizeof(char) * 3);
	if (!str)
		return (error_tokens(2, list));
	ft_strlcpy(str, *line, 3);
	if (*line[0] == '<')
		error = create_token(REDIR_IN_DOUBLE, str, list);
	else
		error = create_token(REDIR_OUT_DOUBLE, str, list);
	if (error)
		return (error_tokens(2, list));
	*line += 2;
	return (0);
}

t_token	*get_tokens(char *line)
{
	t_token	*list;
	int	error;

	list = NULL;
	error = 0;
	while (*line && !error)
	{
		if (ft_strchr(WHITESPACE, *line))
			line++;
		else if (!ft_strncmp(line, "<<", 2) || !ft_strncmp(line, ">>", 2))
			error = process_redirect_2(&line, &list);
		else if (*line == '<' || *line == '>')
			error = process_redirect_1(&line, &list);
		else if (*line == '|')
			error = process_pipe(&line, &list);
		else
			error = process_identifier(&line, &list);
	}
	if (error)
		return (NULL);
	return (list);
}
