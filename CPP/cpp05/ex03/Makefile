NAME = bureaucrat

SRC = main.cpp\
		Bureaucrat.cpp\
		AForm.cpp\
		ShrubberyCreationForm.cpp\
		RobotomyRequestForm.cpp\
		PresidentialPardonForm.cpp\
		Intern.cpp

OBJ = $(SRC:.cpp=.o)

CXX = c++
CXX_FLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME):$(OBJ)
	$(CXX) $(CXX_FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f botanic🌳_shrubbery

re: fclean all

.PHONY: all clean fclean re
