/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:28:38 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/19 17:25:16 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#define WORD 0
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
int		process_env_var(char **line, t_token **list);
int		process_redirect(char **line, char *c, t_token **list);
int		error_tokens(int error, t_token **list);
int		process_string(char **line, t_token **list);
int		find_index(const char *s, int c);

// Token list helpers
void	print_tokens(t_token *token);
void	free_tokens(t_token **list);
void	ft_token_add_back(t_token **lst, t_token *new);

#endif
