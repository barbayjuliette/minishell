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

int	create_hiden_file(t_data *data)
{
	char	*file_name;

	file_name = "tmp.txt";
	data->fd_hdc = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (data->fd_hdc);
}
