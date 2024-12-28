NAME	= pipex

SRCS 	= srcs/main.c srcs/utils.c
OBJS 	= ${SRCS:.c=.o}
MAIN	= srcs/main.c

HEADER	= -Iincludes

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror

.c.o:		%.o : %.c
					@gcc ${CFLAGS} ${HEADER} -c $< -o $@

all: 		${NAME}

${NAME}:	${OBJS}
					@make -C ./libft
					@$(CC) ${OBJS} -Llibft -lft -o ${NAME}

clean:
					@make clean -C ./libft
					@rm -f ${OBJS}

fclean: 	clean
					@make fclean -C ./libft
					@rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re
