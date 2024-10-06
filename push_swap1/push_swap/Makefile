NAME				= push_swap

LIBFT				= ./libft/libft.a
INC					= includes/
SRC_DIR				= srcs/
OBJ_DIR				= obj/

CC					= gcc
CFLAGS				= -Wall -Werror -Wextra -I$(INC)
RM					= rm -f

COMMANDS_DIR		=	$(SRC_DIR)commands/a_to_b.c \
						$(SRC_DIR)commands/b_to_a.c \
						$(SRC_DIR)commands/push.c \
						$(SRC_DIR)commands/swap.c \
						$(SRC_DIR)commands/rotate.c \
						$(SRC_DIR)commands/reverse_rotate.c

PUSH_SWAP_DIR		=	$(SRC_DIR)push_swap/check_stack_utils.c \
						$(SRC_DIR)push_swap/process_stack.c \
						$(SRC_DIR)push_swap/push_swap.c \
						$(SRC_DIR)push_swap/sort_stacks.c \
						$(SRC_DIR)push_swap/sorting_utils.c \

SRCS 				= $(COMMANDS_DIR) $(PUSH_SWAP_DIR)

OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

start:				
					@make all

$(LIBFT):
					@make -C ./libft

all: 				$(NAME)

$(NAME): 			$(OBJ) $(LIBFT)
					@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@

clean:
					@$(RM) -r $(OBJ_DIR)
					@make clean -C ./libft

fclean: 			clean
					@$(RM) $(NAME)
					@$(RM) $(LIBFT)

re: 				fclean all

.PHONY: 			start all clean fclean re
