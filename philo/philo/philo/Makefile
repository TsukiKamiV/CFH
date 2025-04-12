NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror

SRCS = srcs/philo.c\
	   srcs/utils.c\
	   srcs/routine.c\
	   srcs/clean.c\
	   srcs/eat.c\
	   srcs/time.c\
	   srcs/init.c\
	   srcs/death.c\
	   srcs/fork.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS)\
	       -o $(NAME) && \
	echo "[Created] $(NAME) executable."

%.o:%.c
	@$(CC) $(FLAGS) -c $< -o $@ && \
	echo "[philo] $@ created."

clean:
	@rm -f $(OBJS) && echo "[removed] philo objects"

fclean: clean
	@rm -f $(NAME) && echo "[removed] $(NAME) executable"

re: fclean all
.PHONY: all clean fclean re
