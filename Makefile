SRCS	= $(wildcard *.c)

OBJS	= $(SRCS:.c=.o)

NAME	= pipex

CFLAGS	= -Wall -Wextra -Werror

all		: $(NAME)

clean	:
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

re		:
			$(MAKE) fclean
			$(MAKE)	all

$(NAME)	:	$(OBJS)
			$(CC) $(CLFAGS) $^ -o $@

bonus	:	$(NAME)

.PHONY	:	all clean fclean re bonus