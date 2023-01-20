CXX			=	c++

CXXFLAGS	=	-std=c++98 -Wall -Werror -Wextra

SRCS		=	$(wildcard *.cpp)

OBJS		=	$(SRCS:.cpp=.o)

NAME		=	a.out

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CXX) $(CFLAGS) $^ -o $@

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:
				$(MAKE) -C fclean
				$(MAKE) -C all

.PHONY		:	all clean re