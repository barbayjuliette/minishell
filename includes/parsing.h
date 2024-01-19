/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:28:38 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/19 20:20:31 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#define IDENTIFIER 1
#define PIPE 2
#define REDIR_IN_SINGLE 3
#define REDIR_IN_DOUBLE 4
#define REDIR_OUT_SINGLE 5
#define REDIR_OUT_DOUBLE 6

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
int		find_index(const char *s, int c);
int		process_identifier(char **line, t_token **list);
int		is_identifier(char c);

// Token list helpers
void	print_tokens(t_token *token);
void	free_tokens(t_token **list);
void	ft_token_add_back(t_token **lst, t_token *new);

#endif
