/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:32:31 by jbarbay           #+#    #+#             */
/*   Updated: 2024/03/19 11:29:26 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// valgrind --suppressions=readline.supp --leak-check=full
// --show-leak-kinds=all ./minishell

#include "../../includes/minishell.h"

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		(void)signal;
	}
}

char	*configure_signals(void)
{
	char		*line;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	line = readline("minishell$ ");
	return (line);
}

void	execute_and_clean_up(t_data *data, t_token *tokens, t_cmd_table *table)
{
	t_token	*current;

	data->tokens = tokens;
	execute(table, data);
	free_tokens(&tokens, 1);
	free_commands(&table);
	current = data->hd_names;
	if (data->in_file)
	{
		while (current)
		{
			unlink(current->value);
			current = current->next;
		}
	}
	free_tokens(&data->hd_names, 1);
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	char		*line;
	t_token		*tokens;
	t_cmd_table	*table;

	init(&data, envp, argc, argv);
	while (data.exit_flag)
	{
		line = configure_signals();
		if (!line)
			break ;
		if (line && *line)
			add_history(line);
		tokens = get_tokens(line);
		if (!tokens)
			continue ;
		expand_all(tokens, &data);
		remove_empty_tokens(&tokens);
		table = parsing(tokens);
		if (!table)
			continue ;
		execute_and_clean_up(&data, tokens, table);
	}
	clean_before_exit(&data);
	return (data.exit_code);
}
