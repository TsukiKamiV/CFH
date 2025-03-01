NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g3

READLINE_INCLUDE = -I/opt/homebrew/opt/readline/include
READLINE_LIB = -L/opt/homebrew/opt/readline/lib
READLINE_FLAGS = -lreadline -lhistory

LIBFT_PATH = ./libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a

SRCS = minishell.c \
        builtins/env.c \
        builtins/pwd.c \
        builtins/export.c \
		builtins/export_utils.c\
		builtins/export_utils_2.c\
		builtins/export_utils_3.c\
        builtins/unset.c \
        builtins/echo.c \
		builtins/exit.c \
		builtins/cd.c \
		builtins/cd_utils.c \
        data_handling/data_struct_utils.c \
		data_handling/cmd_table_manips.c\
		data_handling/redir_and_heredoc.c\
		data_handling/data_struct_expander.c\
		data_handling/expander_utils.c\
		data_handling/perform_expansion_annexe.c\
        mainloop_handling/minishell_mainloop.c \
        signal_handling/signal_utils.c \
        exec_handling/builtins_exec.c \
		exec_handling/system_exec.c\
		exec_handling/exec_utils.c\
		exec_handling/simple_command_handling.c\
		exec_handling/piped_command_handling.c\
		exec_handling/command_exec.c\
        token_handling/tokenize_input.c \
        token_handling/parse_bools_1.c \
		token_handling/parse_bools_2.c\
		token_handling/token_utils.c\
		token_handling/parse_utils.c\
		token_handling/token_determin_bools.c\
        general_utils/error_exits.c \
        general_utils/string_array_manips.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(FLAGS) $(OBJS) \
	       $(LIBFT_LIB) \
	       $(READLINE_LIB) $(READLINE_FLAGS) \
	       -o $(NAME) && \
	echo "[created] $(NAME) executable."

%.o: %.c
	@$(CC) $(FLAGS) $(READLINE_INCLUDE) -c $< -o $@ && \
	echo "[minishell] $@ created."

clean:
	@rm -f $(OBJS) && echo "[removed] minishell objects"

fclean: clean
	@rm -f $(NAME) && echo "[removed] $(NAME) executable"
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
