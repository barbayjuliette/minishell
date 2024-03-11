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
	int	outfile;

	if (!table->output || !table->output->value)
		outfile = STDOUT_FILENO;
	else
	{
		while (table->output)
		{
			if (table->output->type == 6)
				outfile = open(table->output->value, O_WRONLY | O_CREAT | \
					O_APPEND, 0777);
			else if (table->output->type == 5)
				outfile = open(table->output->value, O_CREAT | O_RDWR | \
					O_TRUNC, 0777);
			if (outfile == -1)
			{
				perror(table->output->value);
				return (-1);
			}
			table->output = table->output->next;
		}
	}
	return (outfile);
}

int	get_fd_in(t_cmd_table *table, t_data *data)
{
	int	infile;

	if (!table->input || !table->input->value)
		infile = STDIN_FILENO;
	else
	{
		while (table->input)
		{
			if (table->input->type == 4)
				infile = data->fd_hdc;
			else
				infile = open(table->input->value, O_RDONLY);
			if (infile == -1)
			{
				perror(table->input->value);
				return (-1);
			}
			table->input = table->input->next;
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
