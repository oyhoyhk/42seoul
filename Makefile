SRCS		=	ft_printf.c						\
				ft_print_integer.c				\
				ft_print_pointer.c				\
				ft_print_hexadecimal.c			\
				ft_print_char_and_string.c		\
				ft_handles.c					\
				ft_utils.c						\

OBJS		= $(SRCS:.c=.o)

LIBFT_DIR	= libft

NAME		= libftprintf.a

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

AR			= ar rcs

INCLUDES	= ./ft_printf.h

all			:	$(NAME)

%.o			:	%.c
				$(CC) $(CFLAGS) -c $< -o $@

clean		:
				$(RM) $(OBJS) 
				$(MAKE) -C $(LIBFT_DIR) fclean

fclean		: 	clean
				$(RM) $(NAME)

re			:	fclean all

$(NAME)		:	$(OBJS)
				$(MAKE) -C $(LIBFT_DIR) all
				cp $(LIBFT_DIR)/libft.a ./$(NAME)
				$(AR) $@ $^

bonus		:	$(NAME)
				
.PHONY		:	all clean fclean re bonus
