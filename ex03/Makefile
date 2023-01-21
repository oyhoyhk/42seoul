CXX			=	c++

CXXFLAGS	=	-std=c++98 -Wall -Werror -Wextra

SRCS		=	$(wildcard *.cpp)

OBJS		=	$(SRCS:.cpp=.o)

NAME		=	main

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CXX) $(CFLAGS) $^ -o $@

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:
				$(MAKE) fclean
				$(MAKE) all

.PHONY		:	all clean re