/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:36:30 by jbarbay           #+#    #+#             */
/*   Updated: 2024/03/11 16:53:11 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "structures.h"
# include "parsing.h"
# include "builtins.h"
# include "exec.h"
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <limits.h>
# include <sys/wait.h>
# include <fcntl.h>

# define WSPACE " \n\t\f\v\r"

int		is_exit(char *line);

// Signals

void	configure_signals(void);
void	handle_sigint(int signal);

#endif
