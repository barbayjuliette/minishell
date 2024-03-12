/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:28:38 by jbarbay           #+#    #+#             */
/*   Updated: 2024/03/12 14:27:16 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define IDENTIFIER 1
# define PIPE 2
# define REDIR_IN_SINGLE 3
# define REDIR_IN_DB 4
# define REDIR_OUT_SINGLE 5
# define REDIR_OUT_DB 6

// Tokenizer
t_token		*get_tokens(char *line);
int			create_token(int type, char *str, t_token **list);
int			process_redirect_1(char **line, t_token **list);
int			process_redirect_2(char **line, t_token **list);
int			process_pipe(char **line, t_token **list);
int			error_tokens(int error, t_token **list);
int			find_index(const char *s, int c);
int			process_identifier(char **line, t_token **list);
int			is_id(char c);

// Token list helpers
void		print_tokens(t_token *token);
void		free_tokens(t_token **list, int i);
void		ft_token_add_back(t_token **lst, t_token *new);

// Parsing
t_cmd_table	*parsing(t_token *token);
t_cmd_table	*init_pipeline(void);
int			get_redirections(t_token *token, t_cmd_table **table);
int			get_length_cmd(t_token *token);
int			get_cmds(t_token *token, t_cmd_table **table);
t_cmd_table	*error_parsing(int i, t_cmd_table **list, t_token **tokens);
t_token		*update_token(t_token *token);

// Parsing list helpers
void		print_all_commands(t_cmd_table *table);
void		print_command_table(t_cmd_table *table);
void		ft_cmds_add_back(t_cmd_table **lst, t_cmd_table *new);
void		free_commands(t_cmd_table **table);

// Expanding
void		expand_variables(char **value, t_data *data);
void		expand_all(t_token *token, t_data *data);
void		remove_quotes(char **value);
char		*update_string_quotes(char *str, int *i, int c);
char		*find_variable_quotes(char *str, int *i, t_data *data);
char		*get_variable(char *str, int *i, int len, t_data *data);
char		*update_string(char *str, int *i, int len, char *value);
char		*get_value_variable(char *str, int i, int len, t_data *data);
int			get_variable_len(char *str);
int			var_is_valid_exp(char c);
void		remove_empty_tokens(t_token **token);

#endif
