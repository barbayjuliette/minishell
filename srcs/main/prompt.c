/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:32:31 by jbarbay           #+#    #+#             */
/*   Updated: 2024/03/12 13:36:08 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell

#include "../../includes/minishell.h"

int	g_status;

int	setup_terminal(bool echo_ctl)
{
	int				status;
	struct termios	terminos_p;

	status = tcgetattr(STDOUT_FILENO, &terminos_p);
	if (status == -1)
		return (1);
	if (echo_ctl)
		terminos_p.c_lflag |= ECHOCTL;
	else
		terminos_p.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_p);
	if (status == -1)
		return (1);
	return (0);
}

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		g_status = 130;
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

	g_status = 0;
	(void)argc;
	(void)argv;
	init(&data, envp);

	setup_terminal(false);
	while (data.exit_flag)
	{
		configure_signals();
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
	return (g_status);
}
