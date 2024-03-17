/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:32:31 by jbarbay           #+#    #+#             */
/*   Updated: 2024/03/13 11:02:08 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell

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

void	configure_signals(void)
{
	signal(SIGINT, handle_sigint); // CTRL+C
	signal(SIGQUIT, SIG_IGN); // CTRL+\.
}

int main(int argc, char **argv, char **envp)
{
	t_data		data;
	char		*line;
	t_token		*tokens;
	t_cmd_table	*table;

	init(&data, envp, argc, argv);
	while (data.exit_flag)
	{
		configure_signals();
		line = readline("minishell$ ");
		if (!line) // To handle CTRL + D
			break ;
		if (line && *line)
			add_history(line);
		tokens = get_tokens(line);
		free(line);
		if (!tokens)
			continue ;
		expand_all(tokens, &data);
		remove_empty_tokens(&tokens);
		table = parsing(tokens);
		data.tokens = tokens;
		if (!table)
			continue ;
		get_number_of_commands(table, &data);
		execute(table, &data);
		//printf("----------------%s\n", data.tmp_name[0]);
		// print_all_commands(table);
		free_tokens(&tokens, 1);
		free_commands(&table);
		dup2(data.original_stdin, STDIN_FILENO);
    	dup2(data.original_stdout, STDOUT_FILENO);
	}
	rl_clear_history();
	free(data.tmp_name);
	if (data.envp != NULL && data.ptr_allocated_by_program != -1)
	{
        free(data.envp);
        //data.envp = NULL;

    }
    
    
	return (data.exit_code);
}
