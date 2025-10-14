NAME = replace
SRCS = main.cpp Replacer.cpp
OBJS = $(SRCS:.cpp=.o)
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -f

all : $(NAME)
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) test.txt.replace

re: fclean all

test: all
	@mkdir -p tests
	@echo "aaa bbb aaa" > tests/small.txt
	@echo "" > tests/empty.txt
	@echo -n "oneline_no_newline" > tests/oneline_no_newline.txt
	@printf "binary\0like\0text\n" > tests/binary_like.txt
	@chmod +x tests/run.sh
	@./tests/run.sh

.PHONY: all clean fclean re test
