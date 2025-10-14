NAME = animalbrain

SRC = main.cpp\
	  Animal.cpp\
	  Cat.cpp\
	  Dog.cpp\
	  Brain.cpp

OBJ = $(SRC:.cpp=.o)

CXX = c++
CXX_FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic

all: $(NAME)

$(NAME):$(OBJ)
	$(CXX) $(CXX_FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
fclean:clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
