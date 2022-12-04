SRCS		=	deque.c						\
				draw_bg.c					\
				draw.c						\
				escape_check.c				\
				ft_handles.c				\
				ft_itoa.c					\
				ft_print_char_and_string.c	\
				ft_print_hexadecimal.c		\
				ft_print_integer.c			\
				ft_print_pointer.c			\
				ft_printf.c					\
				ft_utils.c					\
				handle_event.c				\
				initiate_game.c				\
				parse_map.c					\
				so_long.c					\
				valid_check.c				\
				so_long_utils.c				\
				get_next_line.c				\
				get_next_line_utils.c		\

CFLAGS		=	-Werror -Wextra -Wall

XLMLIB_FLAG	=	-lmlx -framework OpenGL -framework AppKit

OBJS		=	$(SRCS:.c=.o)

NAME		=	so_long

CC			=	cc

RM			=	rm -f

all			:	$(NAME)

clean		:
				$(RM) $(OBJS)

fclean		:	clean
				$(RM) $(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $(XLMLIB_FLAG) -o $@ $^

bonus		:	$(NAME)

re			:
				$(MAKE) fclean
				$(MAKE) all

.PHONY		:	all clean fclean re bonus
