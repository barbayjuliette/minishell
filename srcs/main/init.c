/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:21:16 by akolgano          #+#    #+#             */
/*   Updated: 2024/03/11 14:21:20 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	_ft_init_builtins(t_data *data)
{
	data->builtins[0] = "echo";
	data->builtins[1] = "exit";
	data->builtins[2] = "pwd";
	data->builtins[3] = "cd";
	data->builtins[4] = "export";
	data->builtins[5] = "env";
	data->builtins[6] = "unset";
	data->f_ptrs[0] = &ft_echo;
	data->f_ptrs[1] = &ft_exit;
	data->f_ptrs[2] = &ft_pwd;
	data->f_ptrs[3] = &ft_cd;
	data->f_ptrs[4] = &ft_export;
	data->f_ptrs[5] = &ft_env;
	data->f_ptrs[6] = &ft_unset;
}

int	init(t_data *data, char **envp, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	setup_terminal(false);
	data->exit_code = 0;
	data->exit_flag = 1;
	data->number_of_commands = 0;
	data->envp = envp;
	data->last_command_flag = 0;
	data->outfile = STDOUT_FILENO;
	data->infile = STDIN_FILENO;
	data->delim = NULL;
	data->in_file = NULL;
	data->ptr_allocated_by_program = -1;
	data->blocking_flag = 0;
	data->tmp_name = NULL;
	data->ft_cd_flag = 0;
	data->ft_export_flag = 0;
	data->tmp_names = NULL;
	data->hd_names = NULL;
	data->cd_names = NULL;
	data->fd_hdc = -1;
	_ft_init_builtins(data);
	data->original_stdin = dup(STDIN_FILENO);
	data->original_stdout = dup(STDOUT_FILENO);
	return (0);
}

int	setup_terminal(bool echo_ctl)
{
	int				status;
	struct termios	terminos_p;

	status = tcgetattr(STDOUT_FILENO, &terminos_p);
	if (status == -1)
		return (1);
	if (echo_ctl)
		terminos_p.c_lflag |= ECHOCTL;
	else
		terminos_p.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_p);
	if (status == -1)
		return (1);
	return (0);
}

void	clean_before_exit(t_data *data)
{
	rl_clear_history();
	free_tokens(&data->tmp_names, 1);
	free_tokens(&data->cd_names, 1);
	if (data->envp != NULL && data->ptr_allocated_by_program != -1 \
	&& data->ft_export_flag)
		free(data->envp);
}
