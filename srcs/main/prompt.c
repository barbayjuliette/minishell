/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:32:31 by jbarbay           #+#    #+#             */
/*   Updated: 2024/03/11 16:37:06 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Read line
// Exit when type exit
// Add to history (except if the line is empty)
// Create tokens based on the input
// If tokens is NULL, it means there was an error (with message): new prompt

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell

#include "../../includes/minishell.h"

int	is_exit(char *line)
{
	char	*trimmed;

	if (ft_strlen(line) == 0)
		return (0);
	trimmed = ft_strtrim(line, WSPACE);
	if (ft_strncmp(trimmed, "exit", 5) == 0)
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	return (0);
}

void	handle_sigint(int signal)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signal;
}

void	configure_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
}

int main(int argc, char **argv, char **envp)
{
	t_data		data;
	char		*line;
	t_token		*tokens;
	t_cmd_table	*table;

	configure_signals();

	(void)argc;
	(void)argv;
	init(&data, envp);

	while (data.exit_flag)
	{
		int stdinIsTerminal = isatty(STDIN_FILENO);
    	if (!stdinIsTerminal) 
		{
        	fprintf(stderr, "Error: Standard input is not a terminal.\n");
        	return 1;
    	}
		line = readline("minishell$ ");
		if (!line) // To handle CTRL + D
			break ;
		if (line && *line)
			add_history(line);
		tokens = get_tokens(line);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		// print_tokens(tokens);
		expand_all(tokens, &data);
		table = parsing(tokens);
		if (!table)
		{
			free(line);
			continue ;
		}
		get_number_of_commands(table, &data);
		execute(table, &data);
		// print_all_commands(table);
		free_tokens(&tokens, 1);
		free_commands(&table);
		free(line);
		dup2(data.original_stdin, STDIN_FILENO);
    	dup2(data.original_stdout, STDOUT_FILENO);
	}
	rl_clear_history();
	return (data.exit_code);
}
