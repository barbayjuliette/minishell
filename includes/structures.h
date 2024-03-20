/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:52:04 by jbarbay           #+#    #+#             */
/*   Updated: 2024/03/19 11:06:13 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define NUM_BULTINS 7
# define START_RD_LN 100

typedef struct s_data	t_data;

typedef int				(*t_builtin_ptr)(char **,t_data *);

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd_table
{
	char				**cmds;
	struct s_token		*input;
	struct s_token		*output;
	struct s_cmd_table	*next;

}	t_cmd_table;

struct s_data
{
	int				exit_flag;
	int				exit_code;
	int				infile;
	int				outfile;
	int				number_of_commands;
	int				original_stdin;
	int				original_stdout;
	int				last_command_flag;
	int				fd_hdc;
	int				ptr_allocated_by_program;
	int				blocking_flag;
	int				ft_cd_flag;
	int				ft_export_flag;
	int				hd_flag;
	char			*delim;
	char			**envp;
	char			*tmp_name;
	char			*in_file;
	t_cmd_table		*tbl;
	t_token			*tokens;
	t_token			*tmp_names;
	t_token			*hd_names;
	t_token			*cd_names;
	int				*pipefds;
	char			*builtins[NUM_BULTINS];
	t_builtin_ptr	f_ptrs[NUM_BULTINS];
};

#endif
