/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:52:25 by akolgano          #+#    #+#             */
/*   Updated: 2024/03/11 12:52:27 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler_in_executor(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
		write(2, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		(void)sig;
		write(2, "Quit (core dumped)\n", 19);
	}
}

void	setup_signals(void)
{
	signal(SIGQUIT, handler_in_executor);
	signal(SIGINT, handler_in_executor);
}

int	create_file(int num, char **file_n, t_data *data)
{
	char	*name;

	name = create_name(num, data);
	if (!name)
		return (-1);
	*file_n = name;
	data->fd_hdc = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->fd_hdc == -1)
		free(name);
	return (data->fd_hdc);
}

char	*create_name(int num, t_data *data)
{
	char	*numbr;
	char	*name;

	numbr = ft_itoa(num);
	if (!numbr)
		return ((void *)0);
	name = ft_strjoin("tmp", numbr);
	create_token(0, name, &data->hd_names);
	name = ft_strjoin(name, ".txt");
	create_token(0, name, &data->hd_names);
	free(numbr);
	return (name);
}

void	handler_in_heredoc(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	exit(130);
}
