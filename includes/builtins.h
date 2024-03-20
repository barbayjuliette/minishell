/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:22:30 by akolgano          #+#    #+#             */
/*   Updated: 2024/03/11 14:22:31 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int			init(t_data *data, char **envp, int argc, char **argv);
int			execute(t_cmd_table *table, t_data *data);
int			ft_exit(char **args, t_data *data);
int			ft_echo(char **args, t_data *data);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_callbuiltin(int i, char **cmd, t_data *data);
int			get_number_of_commands(t_cmd_table *table, t_data *data);
void		ft_execve(char **cmd, t_data *data);
int			ft_pwd(char **args, t_data *data);
int			ft_error(void);
int			ft_cd(char **args, t_data *data);
int			ft_export(char **args, t_data *data);
int			ft_env(char **args, t_data *data);
int			ft_unset(char **args, t_data *data);
int			ft_compare(char *str, char *var);
int			print_env(t_data *data);
void		execute_single_command(int i, char **cmd, t_data *data);
int			get_fd(t_cmd_table *table, t_data *data);
int			run_heredoc(t_cmd_table *table, t_data *data);
int			ft_strcontains(const char *s, const char c);
int			ft_compare(char *str, char *var);
int			print_env(t_data *data);
int			var_is_valid(char *line);
char		*ft_getenv(char *name, t_data *data);
int			ft_compare1(const char *str1, const char *str2);
char		*get_value(char *s);
char		*get_name(char *s);
int			add_new_name(char *name, int length, t_data *data);
char		*ft_strdup2(const char *s1);
int			create_hiden_file(t_data *data);
int			get_fd(t_cmd_table *table, t_data *data);
int			check_if_builtins(char *str, t_data *data);
char		*add_var_evp_02(char *name, int flag, int length, t_data *data);
void		add_new_name_02(char *name, char **tmp_env, int i, t_data *data);
int			find_name(char *name, t_data *data);
void		change_name(char *name, char *tmp_name, int i, t_data *data);
int			check_name_02(char *name, char flag, int i);
int			find_value(int i, t_data *data);
int			check_name(char *name, char flag);
char		*ft_getenv_for_env(char *name, t_data *data);
void		add_var_evp(char *name, int flag, t_data *data);
void		handle_error_blocking(char **cmd, t_data *data);
void		clean_before_exit(t_data *data);
int			process(int *pipefds, t_cmd_table *table, t_data *data);
int			create_process(t_cmd_table *table, t_data *data);
void		setup_pipes(int *pipefds, t_data *data);
void		setup_signals(void);
void		handler_in_executor(int sig);
int			create_file(int num, char **file_n, t_data *data);
char		*create_name(int num, t_data *data);
void		handler_in_heredoc(int sig);
int			execute_commands(int *pipefds, t_cmd_table *table, \
			t_data *data, int j);
#endif
