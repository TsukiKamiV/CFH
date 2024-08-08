##all:
##gcc -L./mlx -lmlx -framework OpenGL -framework AppKit main.c
##./a.out

NAME = so_long

LIBFT = ./libs/libft/libft.a

FT_PRINTF = ./libs/ft_printf/libftprintf.a

CC = clang

STANDARD_FLAGS = -Wall -Wextra -Werror
MINILIB_FLAGS = -lmlx -framework OpenGL -framework Appkit

SRCS_DIR = ./src/

SRCS = $(addprefix $(SRCS_DIR),\
			main.c \
			ft_verify_map.c)

all:	${LIBFT} ${FT_PRINTF}  ${NAME}

${NAME}:
		${CC} ${SRCS} ${LIBFT} ${FT_PRINTF} ${STANDARD_FLAGS} ${MINILIBX_FLAGS} -o ${NAME}


${LIBFT}:
		make bonus -C libs/libft
${FT_PRINTF}:
		make -C libs/ft_printf

clean:
		make clean -C libs/libft
		make clean -C libs/ft_printf
fclean:
		rm -f ${NAME}
re:		fclean all

.PHONY:	all clean fclean re
