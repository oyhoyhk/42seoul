NAME		=	ircserv
CXX			=	c++
RM			=	rm -rf
CXXFLAGS	=	-std=c++98 -MMD #-Wall -Werror -Wextra
SRC_DIR		=	srcs/
HEADERS_DIR	=	includes/ includes/Server/
CINCLUDE	=	-I$(HEADERS_DIR)

SRCS		=	$(wildcard srcs/*.cpp) $(wildcard srcs/**/*.cpp)
OBJS		=	$(SRCS:.cpp=.o)
DEPS		=	$(SRCS:.cpp=.d)

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CXX) $(CXXFLAGS) $^ -o $@

clean		:
				$(RM) $(OBJS)
				$(RM) $(DEPS)

fclean		:
				$(MAKE) clean
				$(RM) $(NAME)

re			:
				$(MAKE) fclean
				$(MAKE) all

.PHONY		:	all clean re fclean
