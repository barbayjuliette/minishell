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
		str = readline("> ");
		if (ft_strcmp(str, data->delim) == 0)
			break ;
		ft_putstr_fd(str, data->fd_hdc);
		ft_putstr_fd("\n", data->fd_hdc);
		free(str);
	}
	free_tokens(&data->tokens, 1);
	free_commands(&data->tbl);
	free_tokens(&data->hd_names, 1);
	exit(0);
}

int	ft_heredoc(t_data *data, int num)
{
	int			pid;
	int			res;
	char		*file_n;

	data->fd_hdc = create_file(num, &file_n, data);
	data->in_file = file_n;
	pid = fork();
	if (pid == -1)
		return (START_RD_LN);
	if (pid == 0)
	{
		signal(SIGINT, (void (*)(int))handler_in_heredoc);
		signal(SIGQUIT, SIG_IGN);
		child(data);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(-1, &res, 0);
	}
	return (0);
}

int	create_heredoc(t_cmd_table *table, int num, t_data *data)
{
	t_token	*lst;

	lst = table->input;
	while (lst)
	{
		if (lst->type == 4)
		{
			data->delim = lst->value;
			ft_heredoc(data, num);
		}
		lst = lst->next;
	}
	return (0);
}

int	run_heredoc(t_cmd_table *table, t_data *data)
{
	t_cmd_table	*tmp_cmd;
	int			num;

	tmp_cmd = table;
	num = 1;
	while (tmp_cmd)
	{
		if (create_heredoc(tmp_cmd, num, data))
			return (1);
		tmp_cmd = tmp_cmd->next;
		num++;
	}
	return (0);
}
