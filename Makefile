SRCS = prompt.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
NAME = minishell
OBJS = ${SRCS:.c=.o}

all: ${NAME}

$(NAME):
		@make all -C libft
		$(CC) $(CFLAGS) $(SRCS) -L./libft -lft -L/usr/local/lib -I/usr/local/include -lreadline -o ${NAME}

%.o: %.c
	${CC} $(CFLAGS) -c $<

clean:
		${RM} ${OBJS}
		@make fclean -C libft

fclean: clean
		${RM} ${NAME} ${OBJS}

re: fclean all

.PHONY: all clean fclean re
