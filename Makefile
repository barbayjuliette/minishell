MAIN = srcs/main/prompt.c \
		srcs/main/init.c \
		srcs/parsing/lexer.c \
		srcs/parsing/list_helpers.c \
		srcs/parsing/strings.c \
		srcs/parsing/parsing.c \
		srcs/parsing/parsing_helpers.c \
		srcs/parsing/expander.c \
		srcs/parsing/expander_helpers.c \
		srcs/parsing/remove_quotes.c \
		srcs/builtins/ft_exit.c \
		srcs/builtins/ft_echo.c \
		srcs/builtins/ft_pwd.c \
		srcs/builtins/ft_cd.c \
		srcs/builtins/ft_export.c \
		srcs/builtins/ft_export_utils.c \
		srcs/builtins/ft_export_names.c \
		srcs/builtins/ft_env.c \
		srcs/builtins/ft_unset.c \
		srcs/builtins/execute.c \
		srcs/builtins/execute_utils.c \
		srcs/builtins/call_builtin.c \
		srcs/builtins/call_execve.c \
		srcs/builtins/heredoc.c \
		srcs/builtins/heredoc_utils.c \
		srcs/builtins/utils.c \
		srcs/builtins/utils2.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
NAME = minishell
OBJS = ${MAIN:.c=.o}

all: ${NAME}

$(NAME):
		@echo "Compiling"
		@make all -C libft
		$(CC) $(CFLAGS) $(MAIN) -L./libft -lft -L/usr/local/lib -I/usr/local/include -lreadline -o ${NAME} && echo "Everything compiled!"

%.o: %.c
	${CC} $(CFLAGS) -c $<

clean:
		${RM} ${OBJS}
		@make fclean -C libft

fclean: clean
		${RM} ${NAME} ${OBJS}

re: fclean all

.PHONY: all clean fclean re

.PRECIOUS: ${OBJS}

.SILENT: all clean fclean re
