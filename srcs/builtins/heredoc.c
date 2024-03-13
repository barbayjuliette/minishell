/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:54:44 by akolgano          #+#    #+#             */
/*   Updated: 2024/02/27 14:54:45 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child(t_data *data)
{
	char	*str;

	while (1)
	{
		signal(SIGQUIT, SIG_DFL); // CTRL+\.
		signal(SIGINT, SIG_DFL); // CTRL+C
		str = readline("> ");
		if (ft_strcmp(str, data->delim) == 0)
			break ;
		ft_putstr_fd(str, data->fd_hdc);
		ft_putstr_fd("\n", data->fd_hdc);
		free(str);
	}
	exit(0);
}

int	parent(t_data *data)
{
	int	res;

	waitpid(-1, &res, 0);
	data->fd_hdc = open("tmp.txt", O_RDWR);
	return (0);
}

int	ft_heredoc(t_data *data)
{
	int	pid;

	data->fd_hdc = create_hiden_file(data);
	if (data->fd_hdc == START_RD_LN)
		return (START_RD_LN);
	pid = fork();
	if (pid == -1)
		return (START_RD_LN);
	if (pid == 0)
		child(data);
	else
	{
		if (parent(data) == START_RD_LN)
			return (START_RD_LN);
	}
	return (data->fd_hdc);
}

int	run_heredoc(t_cmd_table *table, t_data *data)
{
	t_cmd_table	*tmp;

	tmp = copylinkedlist(table);
	while (tmp->input)
	{
		if (tmp->input->type == 4)
		{
			data->delim = tmp->input->value;
			ft_heredoc(data);
		}
		tmp->input = tmp->input->next;
	}
	return (0);
}
