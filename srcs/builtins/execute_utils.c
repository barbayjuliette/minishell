/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:41:52 by akolgano          #+#    #+#             */
/*   Updated: 2024/03/11 13:41:56 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_fd_out(t_cmd_table *table)
{
	int		outfile;
	t_token	*lst;

	lst = table->output;
	if (!lst || !lst->value)
		outfile = STDOUT_FILENO;
	else
	{
		while (lst)
		{
			if (lst->type == 6)
				outfile = open(lst->value, O_WRONLY | O_CREAT | \
					O_APPEND, 0777);
			else if (table->output->type == 5)
				outfile = open(lst->value, O_CREAT | O_RDWR | \
					O_TRUNC, 0777);
			if (outfile == -1)
			{
				perror(lst->value);
				return (-1);
			}
			lst = lst->next;
		}
	}
	return (outfile);
}

int	get_fd_in(t_cmd_table *table, t_data *data)
{
	int		infile;
	t_token	*lst;

	lst = table->input;
	if (!lst || !lst->value)
		infile = STDIN_FILENO;
	else
	{
		while (lst)
		{
			if (lst->type == 4)
			{
				infile = open(data->in_file, O_RDONLY, 0644);
			}
			else
				infile = open(lst->value, O_RDONLY);
			if (infile == -1)
			{
				perror(lst->value);
				return (-1);
			}
			lst = lst->next;
		}
	}
	return (infile);
}

int	get_fd(t_cmd_table *table, t_data *data)
{
	data->outfile = get_fd_out(table);
	data->infile = get_fd_in(table, data);
	if (data->outfile == -1 || data->infile == -1)
		return (1);
	return (0);
}

int	check_if_builtins(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (i < NUM_BULTINS)
	{
		if (ft_strcmp(str, data->builtins[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

int	get_number_of_commands(t_cmd_table *table, t_data *data)
{
	int	i;

	i = 0;
	while (table)
	{
		table = table->next;
		i++;
	}
	data->number_of_commands = i;
	return (i);
}
