NAME = libftprintf.a
  
LIBFT_NAME = libft.a

LIBFT_PATH = ./libft

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRCS = ft_print.c\
       print_char.c\
       print_string.c\
       print_int.c\
       print_unsigned.c\
       print_hex.c\
       print_pointer.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

makelibft:
	$(MAKE) -C $(LIBFT_PATH)
	cp $(LIBFT_PATH)/$(LIBFT_NAME) .

$(NAME): makelibft $(OBJS)
	ar -r $(NAME) $(LIBFT_NAME) $(OBJS)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME) $(LIBFT_NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all
