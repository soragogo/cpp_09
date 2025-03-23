NAME=btc

CXX=c++

CXXFLAGS=-Wall -Wextra -Werror -std=c++98

SRCS=main.cpp BitcoinExchange.cpp

OBJDIR=objs

OBJS=$(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))


all:$(NAME)

$(NAME):$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean:clean
	rm -rf $(NAME)

re:fclean
	make all

debug: CXXFLAGS += -g -O0 -fsanitize=address
debug: fclean all
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

.PHONY:		clean fclean all re debug
