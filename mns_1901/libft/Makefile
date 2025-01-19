CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRC = ft_atoi.c		\
	ft_calloc.c		\
	ft_isalnum.c	\
	ft_isalpha.c	\
	ft_isascii.c	\
	ft_isdigit.c	\
	ft_isprint.c	\
	ft_memchr.c		\
	ft_memcmp.c		\
	ft_memcpy.c		\
	ft_memset.c		\
	ft_putchar_fd.c	\
	ft_putendl_fd.c	\
	ft_putnbr_fd.c	\
	ft_putstr_fd.c	\
	ft_strchr.c		\
	ft_strdup.c		\
	ft_strjoin.c	\
	ft_strlen.c		\
	ft_strmapi.c	\
	ft_strncmp.c	\
	ft_strnstr.c	\
	ft_strrchr.c	\
	ft_strtrim.c	\
	ft_substr.c		\
	ft_tolower.c	\
	ft_toupper.c	\
	ft_bzero.c		\
	ft_strlcpy.c	\
	ft_strlcat.c	\
	ft_split.c		\
	ft_striteri.c	\
	ft_memmove.c	\
	ft_itoa.c		\
	get_next_line_bonus.c \
	get_next_line_utils_bonus.c \

BSRC = ft_lstnew.c	\
	ft_lstadd_front.c \
	ft_lstsize.c	\
	ft_lstlast.c	\
	ft_lstadd_back.c	\
	ft_lstdelone.c	\
	ft_lstclear.c	\
	ft_lstiter.c	\
	ft_lstmap.c	 \

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
MAGENTA = \033[0;35m
RESET = \033[0m

# Dégradé de YELLOW à rouge
GRADATION1_YELLOW = \033[38;5;220m
GRADATION2_YELLOW = \033[38;5;214m
GRADATION3_YELLOW = \033[38;5;208m
GRADATION4_YELLOW = \033[38;5;202m

# $@ : nom de la cible
# $< : nom de la première dépendance
# $^ : liste des dépendances
# $? : liste des dépendances plus récentes que la cible
# $* : nom du fichier sans suffixe

BOBJ = $(BSRC:.c=.o)

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@ar -rcs $(NAME) $(OBJ) && echo "[$(GREEN)created$(RESET)]$(NAME) created."

%.o : %.c
    # $< Target (.o) | $@ = all
	@$(CC) $(FLAGS) -c $< -o $@ && echo "[$(YELLOW)Libft$(RESET)] $@ created."

bonus : $(OBJ) $(BOBJ)
	@ar -rcs $(NAME) $(OBJ) $(BOBJ) && echo "$(NAME) created with bonus."

clean :
	@rm -f $(OBJ) $(BOBJ) && echo "[$(GRADATION4_YELLOW)removed$(RESET)] libft objects"

fclean : clean
	@rm -f $(NAME) && echo "[$(GRADATION4_YELLOW)removed$(RESET)] $(NAME)"

re : fclean all

.PHONY : all clean fclean re
