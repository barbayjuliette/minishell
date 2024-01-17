/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:28:38 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/17 21:40:05 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#define STRING 0
#define SINGLE 1
#define DOUBLE 2
#define PIPE 3
#define REDIR 4
#define ENV_VAR 5

typedef struct s_token
{
	int	type;
	char *value;
	struct s_token *next;
}	t_token;

t_token	*get_tokens(char *line);
void	create_token(int type, char *str, t_token **list);
void	ft_token_add_back(t_token **lst, t_token *new);
void	print_tokens(t_token *token);

#endif
