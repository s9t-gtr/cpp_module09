CPPS = main.cpp BitcoinExchange.cpp

OBJS = $(CPPS:%.cpp=$(OBJS_DIR)/%.o)

DEPS = $(CPPS:%.cpp=$(DEPS_DIR)/%.d)

NAME = btc
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

OBJS_DIR = objs
DEPS_DIR = deps

$(OBJS_DIR)/%.o: %.cpp 
	@mkdir -p $(OBJS_DIR) $(DEPS_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c -MMD -MP -MF  $(addprefix $(DEPS_DIR)/, $(notdir $(@:%.o=%.d))) $<

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: all clean fclean re
all: $(NAME);

clean: 
	rm -rf $(OBJS_DIR)
	rm -rf $(DEPS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all;


-include ${DEPS}
