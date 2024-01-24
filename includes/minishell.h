/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:36:30 by jbarbay           #+#    #+#             */
/*   Updated: 2024/01/18 13:11:58 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include "parsing.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

# define RED "\001\e[1m\e[31m\002"
# define GREEN "\001\e[1m\e[32m\002"
# define YELLOW "\033[1;33m"
# define DEFAULT "\001\033[0;39m\002"
# define WHITESPACE " \n\t\f\v\r"

int		is_exit(char *line);

#endif
