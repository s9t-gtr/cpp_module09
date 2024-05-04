CPPS = main.cpp PmergeMe.cpp

OBJS = ${CPPS:.cpp=.o}

DEPS = $(CPPS:.cpp=.d)

NAME = PmergeMe
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3 -MMD

-include $(DEPS);

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
.PHONY: all clean fclean re
all: $(NAME);

clean: 
	rm -f $(OBJS)
	rm -f *.d
fclean: clean
	rm -f $(NAME)

re: fclean all;
