MAIN = srcs/main/prompt.c \
		srcs/parsing/lexer.c \
		srcs/parsing/list_helpers.c \
		srcs/parsing/strings.c \
		srcs/parsing/parsing.c \
		srcs/parsing/parsing_helpers.c \
		srcs/parsing/expander.c \
		srcs/parsing/expander_helpers.c \
		srcs/parsing/remove_quotes.c \

CC = gcc -std=gnu99
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = minishell
OBJS = ${MAIN:.c=.o}

all: ${NAME}

# Removed the flags at compilation for testing

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
