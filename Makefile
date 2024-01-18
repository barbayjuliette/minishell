MAIN = srcs/main/prompt.c \
		srcs/parsing/lexer.c \
		srcs/parsing/list_helpers.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = minishell
OBJS = ${MAIN:.c=.o}

all: ${NAME}

$(NAME):
		@make all -C libft
		$(CC) $(MAIN) -L./libft -lft -L/usr/local/lib -I/usr/local/include -lreadline -o ${NAME}

%.o: %.c
	${CC} $(CFLAGS) -c $<

clean:
		${RM} ${OBJS}
		@make fclean -C libft

fclean: clean
		${RM} ${NAME} ${OBJS}

re: fclean all

.PHONY: all clean fclean re
