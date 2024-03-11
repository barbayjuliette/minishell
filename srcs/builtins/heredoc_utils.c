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

t_cmd_table	*copylinkedlist(t_cmd_table	*head)
{
	t_cmd_table	*newhead;
	t_cmd_table	*tail;
	t_cmd_table	*newnode;

	newhead = NULL;
	tail = NULL;
	while (head != NULL)
	{
		newnode = (t_cmd_table *)malloc(sizeof(t_cmd_table));
		newnode->input = head->input;
		newnode->next = NULL;
		if (newhead == NULL)
		{
			newhead = newnode;
			tail = newnode;
		}
		else
		{
			tail->next = newnode;
			tail = newnode;
		}
		head = head->next;
	}
	return (newhead);
}

int	create_hiden_file(t_data *data)
{
	char	*file_name;

	file_name = "tmp.txt";
	data->fd_hdc = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (data->fd_hdc);
}
