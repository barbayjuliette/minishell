/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:28:38 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/18 18:42:34 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#define STRING 0
#define SINGLE 1
#define DOUBLE 2
#define PIPE 3
#define ENV_VAR 4
#define REDIR_IN_SINGLE 5
#define REDIR_IN_DOUBLE 6
#define REDIR_OUT_SINGLE 7
#define REDIR_OUT_DOUBLE 8

typedef struct s_token
{
	int	type;
	char *value;
	struct s_token *next;
}	t_token;

// Tokenizer
t_token	*get_tokens(char *line);
void	create_token(int type, char *str, t_token **list);
int		process_quote(char **line, int quote, t_token **list);
int		process_pipe(t_token **list);
int		process_variable(char **line, t_token **list);
int		process_input(char **line, char *c, t_token **list);
int		error_tokens(int error, t_token **list);


// Token list helpers
void	print_tokens(t_token *token);
void	free_tokens(t_token **list);
void	ft_token_add_back(t_token **lst, t_token *new);

#endif
