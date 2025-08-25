NAME = so_long

LIBFT = ./libft/libft.a
MLX = ./mlx/libmlx.a
INC = ./includes/
SRC_DIR = src/
OBJ_DIR = obj/

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC)
//MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
MLX_FLAGS = -Lmlx -lmlx -lX11 -lXext -lm
RM = rm -f

SOLONG_DIR = $(SRC_DIR)main.c\
				$(SRC_DIR)ft_verify_map.c\
				$(SRC_DIR)ft_init_window.c\
				$(SRC_DIR)ft_verify_path.c\
				$(SRC_DIR)ft_verify_path_utils.c\
				$(SRC_DIR)ft_init_map.c\
				$(SRC_DIR)ft_put_floor.c\
				$(SRC_DIR)ft_init_images.c\
				$(SRC_DIR)ft_render_map.c\
				$(SRC_DIR)ft_manage_event.c\
				$(SRC_DIR)ft_exit_game.c\
				$(SRC_DIR)ft_destroy.c

SRCS = $(SOLONG_DIR)
OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

start:
		@make all
$(LIBFT):
		@make -C ./libft

$(MLX):
		@make -C ./mlx

all:	$(NAME)

$(NAME):	$(OBJ) $(LIBFT) $(MLX)
			  @$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

clean:			
				@$(RM) -r $(OBJ_DIR)
				@make clean -C ./libft
				@make clean -C ./mlx

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) $(LIBFT)
				@$(RM) $(MLX)
re:				fclean all

.PHONY:			start all clean fclean

