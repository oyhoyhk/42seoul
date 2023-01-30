NAME		=	ircserv
CXX			=	c++
#CXXFLAGS	=	-std=c++98 -Wall -Werror -Wextra
SRC_DIR		=	srcs/
HEADERS_DIR	=	includes/ includes/Server/
CINCLUDE	=	-I$(HEADERS_DIR)

SRCS		=	$(wildcard srcs/*.cpp) srcs/Server/Server.cpp
OBJS		=	$(SRCS:.cpp=.o)

all			:	$(NAME)

%.o			:	%.c
				$(CXX) $(CXXFLAGS) $(CINCLUDE) -c $< -o $@

$(NAME)		:	$(OBJS)
				$(CXX) $(CXXFLAGS) $^ -o $@

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:
				$(MAKE) fclean
				$(MAKE) all

.PHONY		:	all clean re fclean