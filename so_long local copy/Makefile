NAME = so_long

CC = clang

CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

SRCS_DIR = ./src/
LIBFT_DIR = ./libs/libft/
MLX_DIR = ./mlx/

LIBFT_FILE = libft.a
MLX_FILE = libmlx.a

LIBFT_LIB = $(addprefix $(LIBFT_DIR), $(LIBFT_FILE))
MLX_LIB = $(addprefix $(MLX_DIR), $(MLX_FILE))

MLX_EX = $(MLX_LIB) $(MLX_FLAGS)

C_FILE = main.c\
			ft_verify_map.c\
			ft_init_window.c\
			ft_init_map.c\
			ft_put_floor.c\
			ft_render_map.c\
			ft_manage_event.c\
			ft_exit_game.c

INC_DIR = ./includes/

SRCS = $(addprefix $(SRCS_DIR),$(C_FILE))

OBJ = $(SRCS:.c=.o)

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)

libft:
		make -C $(LIBFT_DIR)
mlx:
		make -sC $(MLX_DIR)

${NAME}: libft $(OBJ)
	$(CC) $(OBJ) $(LIBFT_LIB) $(MLX_FILE) -o $(NAME)

clean:
		@make clean -sC $(MLX_DIR)
		@make clean -sC $(LIBFT_DIR)
		@rm -f ${OBJ}
fclean:
		clean
		@rm -f ${NAME}
		@make fclean -C $(LIBFT_DIR)

re:		fclean all

run:	${NAME}
		./{NAME}

.PHONY:	all clean fclean re run
