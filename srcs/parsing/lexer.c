/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:32:45 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/18 16:23:42 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_quote(char **line, int quote, t_token **list)
{
	int		i;
	char	*str;

	i = 1;
	if (!ft_strchr(*line + 1, quote))
	{
		printf("Syntax error: unclosed quotes\n");
		free_tokens(list);
		return (-1);
	}
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

int	process_variable(char **line, t_token **list)
{
	int	i;
	char	*str;

	i = 1;
	if (ft_isdigit((*line)[i]))
	{
		printf("Environment variable cannot start with a digit\n");
		free_tokens(list);
		return (-1);
	}
	while ((*line)[i] && !ft_strchr(WHITESPACE, (*line)[i]))
	{	
		if (!ft_isalnum((*line)[i]) && (*line)[i] != '_')
		{
			printf("Only uppercase, lowercase, and underscores are allowed for environment variables\n");
			free_tokens(list);
			return (-1);
		}
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

t_token	*get_tokens(char *line)
{
	t_token *list;

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
			line++;
	}
	return (list);
}

void	create_token(int type, char *str, t_token **list)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	// if (!new)
	// 	return (NULL);
	new->type = type;
	new->value = str;
	new->next = NULL;
	ft_token_add_back(list, new);
}

void	ft_token_add_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
}

void	print_tokens(t_token *token)
{
	int	i;

	i = 0;
	printf("Printing TOKENS: \n");
	while (token)
	{
		printf("Item %d:, type: %d, value: %s\n", i, token->type, token->value);
		i++;
		token = token->next;
	}
}

void	free_tokens(t_token **list)
{
	t_token	*current;
	t_token	*next;

	current = *list;
	while (current)
	{
		next = current->next;
		free(current->value);
		current->value = NULL;
		free(current);
		current = next;
	}
	*list = NULL;
}

