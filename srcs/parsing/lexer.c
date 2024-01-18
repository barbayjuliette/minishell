/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:32:45 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/18 14:01:01 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_quote(char *line, int quote, t_token **list)
{
	int		i;
	char	*str;

	i = 1;
	if (!ft_strchr(line + 1, quote))
	{
		printf("Syntax error: unclosed quote\n");
		free_tokens(list);
		return (-1);
	}
	while (line [i] && line[i] != quote)
		i++;
	i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	ft_strlcpy(str, line, i + 1);
	if (quote == 34)
		create_token(DOUBLE, str, list);
	else
		create_token(SINGLE, str, list);
	return (i);
}

int	process_variable(int type, char *line, t_token **list)
{
	int	i;
	char	*str;

	i = 1;
	if (ft_isdigit(line[i]))
	{
		printf("Environment variable cannot start with a digit\n");
		free_tokens(list);
		return (-1);
	}
	while (line[i] && !ft_strchr(WHITESPACE, line[i]))
	{	
		if (!ft_isalnum(line[i]) && line[i] != '_')
		{
			printf("Only uppercase, lowercase, and underscores are allowed for environment variables\n");
			free_tokens(list);
			return (-1);
		}
		i++;
	}
	str = (char *)malloc(sizeof(char) * (i + 1));
	ft_strlcpy(str, line, i + 1);
	create_token(ENV_VAR, str, list);
	return (i);
}

int	process_pipe(int type, t_token **list)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	str[0] = '|';
	str[1] = '\0';
	create_token(PIPE, str, list);
	return (1);
}

t_token	*get_tokens(char *line)
{
	int	i;
	int	j;
	t_token *list;

	i = 0;
	j = 0;
	list = NULL;
	while (line[i])
	{
		if (ft_strchr(WHITESPACE, line[i]))
			i++;
		else if (line[i] == 34)
		{
			if ((j = process_quote(line + i, 34, &list)) == -1)
				return (NULL); // + free list
			i += j;
		}
		else if (line[i] == 39)
		{
			if ((j = process_quote(line + i, 39, &list)) == -1)
				return (NULL);
			i += j;
		}
		else if (line[i] == '$')
		{
			if ((j = process_variable(ENV_VAR, line + i, &list)) == -1)
				return (NULL);
			i += j;
		}
		else if (line[i] == '|')
			i += process_pipe(PIPE, &list);
		else
			i++;
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

