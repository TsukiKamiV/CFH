LIBC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c\
       ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c\
       ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c\
       ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c\
       ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c

ADDITIONAL = ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c\
	     ft_split.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_substr.c ft_striteri.c

FT_PRINTF = ft_printf.c \
			print_char.c \
			print_hex.c \
			print_int.c \
			print_pointer.c \
			print_string.c \
			print_unsigned.c

GNL = get_next_line.c

SRCS = ${LIBC} ${ADDITIONAL} ${FT_PRINTF} ${GNL}

OBJS = ${SRCS:.c=.o}

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I ./

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
		ar rcs ${NAME} ${OBJS}

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean:
	rm -f ${OBJS} ${NAME}

re:	fclean all

.PHONY: all clean fclean re
