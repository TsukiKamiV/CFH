# **************************************************************************** #
#                                miniRT Makefile                               #
# **************************************************************************** #

NAME = miniRT

# 路径配置
SRC_DIR = srcs/
OBJ_DIR = obj/
INC = includes/

LIBFT = ./libft/libft.a
MLX = ./mlx/libmlx.a

# 编译器与参数
CC = gcc
#CFLAGS = -Wall -Wextra -Werror -I$(INC)
#MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
# 如果你在Linux上编译，则取消下面一行注释并注释掉上面一行
#MLX_FLAGS = -Lmlx -lmlx -lX11 -lXext -lm

# 编译器与参数（自动检测平台；可用 make TARGET_OS=Linux 或 TARGET_OS=Darwin 覆盖）
CFLAGS  = -Wall -Wextra -Werror -I$(INC)

# 平台检测：默认取 uname -s；允许用 TARGET_OS 手动覆盖（Darwin 或 Linux）
TARGET_OS ?= $(shell uname -s)

ifeq ($(TARGET_OS),Darwin)
    # macOS 使用 Cocoa 版 MiniLibX
    MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
    CFLAGS   += -DMRT_MACOS
else ifeq ($(TARGET_OS),Linux)
    # Linux 使用 X11 版 MiniLibX
    MLX_FLAGS = -Lmlx -lmlx -lX11 -lXext -lm
    CFLAGS   += -DMRT_LINUX
else
    $(error Unsupported OS: $(TARGET_OS). Use TARGET_OS=Darwin or TARGET_OS=Linux)
endif

# 源文件
SRC_FILES = \
	main.c \
	free/exit_free.c \
	exit/close_window.c \
	math/vec3.c \
	math/vec3_bis.c \
	render/render_scene.c \
	render/ray.c \
	render/ray_hit.c \
	render/ray_utils.c \
	render/ambient.c \
	render/lighting.c \
	render/diffuse.c \
	render/ray_hit_pl.c\
	render/ray_hit_sp.c\
	render/ray_hit_cy.c\
	render/ray_hit_cy_annex.c\
	utils/utils.c \
	utils/utils_2.c\
	utils/error.c \
	utils/img_utils.c \
	init/hook.c \
	init/read_file.c \
	init/parse_utils.c\
	init/parse_scene/parse_amb.c\
	init/parse_scene/parse_cam.c\
	init/parse_scene/parse_light.c\
	init/parse_obj/parse_plane.c\
	init/parse_obj/parse_sphere.c\
	init/parse_obj/parse_cylinder.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# 编译目标
all: $(NAME)

$(LIBFT):
	@make -C libft

$(MLX):
	@make -C mlx

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ Build complete: $(NAME)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@echo "[Compile] $< ➜ $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# 颜色和符号
GREEN  = \033[1;32m
YELLOW = \033[1;33m
BLUE   = \033[1;34m
RESET  = \033[0m
CHECK  = ✅
CLEAN  = 🧹

clean:
	@echo "🧹 [clean] Removing miniRT object files..."
	@rm -rf $(OBJ_DIR)
	@echo "🧹 [clean] Cleaning libft..."
	-@$(MAKE) -C libft clean > /dev/null || echo "libft clean skipped"
	@echo "🧹 [clean] Cleaning mlx..."
	@if [ -f mlx/Makefile ]; then \
		$(MAKE) -C mlx clean > /dev/null || echo "mlx clean failed"; \
	else \
		echo "mlx Makefile not found. Skipping mlx clean."; \
	fi

fclean: clean
	@echo "🧹 [fclean] Removing executable $(NAME)..."
	@rm -f $(NAME)
	@echo "🧹 [fclean] Running libft fclean..."
	-@$(MAKE) -C libft fclean > /dev/null || echo "libft fclean skipped"
	@echo "🧹 [fclean] Running mlx fclean..."
	@if [ -f mlx/Makefile ]; then \
		$(MAKE) -C mlx fclean > /dev/null || echo "mlx fclean failed"; \
	else \
		echo "mlx Makefile not found. Skipping mlx fclean."; \
	fi

re: fclean all
.PHONY: all clean fclean re
