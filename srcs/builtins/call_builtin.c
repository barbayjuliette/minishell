/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:05:33 by akolgano          #+#    #+#             */
/*   Updated: 2024/02/27 14:05:39 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_callbuiltin(int i, char **cmd, t_data *data)
{
	(*data->f_ptrs[i])(cmd, data);
	exit(0);
}

void	execute_single_command(int i, char **cmd, t_data *data)
{
	int	original_stdin;
	int	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (data->infile != STDIN_FILENO && data->infile != -1)
	{
		if (dup2(data->infile, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(data->infile);
	}
	if (data->outfile != STDOUT_FILENO && data->outfile != -1)
	{
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(data->outfile);
	}
	(*data->f_ptrs[i])(cmd, data);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}
