# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 12:35:52 by yooh              #+#    #+#              #
#    Updated: 2022/11/11 14:33:24 by yooh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= ft_atoi.c			\
		  ft_bzero.c		\
		  ft_calloc.c		\
		  ft_isalnum.c		\
		  ft_isalpha.c		\
		  ft_isascii.c		\
		  ft_isdigit.c		\
		  ft_isprint.c		\
		  ft_memchr.c		\
		  ft_memcpy.c		\
		  ft_memmove.c		\
		  ft_memset.c		\
		  ft_strchr.c		\
		  ft_strlcat.c		\
		  ft_strlcpy.c		\
		  ft_strlen.c		\
		  ft_strncmp.c		\
		  ft_strnstr.c		\
		  ft_strrchr.c		\
		  ft_tolower.c		\
		  ft_toupper.c		\
		  ft_memcmp.c		\
		  ft_strdup.c		\
		  ft_substr.c		\
		  ft_strjoin.c		\
		  ft_strtrim.c		\
		  ft_split.c		\
		  ft_itoa.c			\
		  ft_strmapi.c		\
		  ft_striteri.c		\
		  ft_putchar_fd.c	\
		  ft_putstr_fd.c	\
		  ft_putendl_fd.c	\
		  ft_putnbr_fd.c	

SRC_B	= ft_lstnew.c		\
		  ft_lstadd_front.c	\
		  ft_lstsize.c		\
		  ft_lstlast.c		\
		  ft_lstadd_back.c	\
		  ft_lstdelone.c	\
		  ft_lstclear.c		\
		  ft_lstiter.c		\
		  ft_lstmap.c

OBJS		= $(SRC:.c=.o)

OBJS_B		= $(SRC_B:.c=.o)

NAME		= libft.a

CC			= gcc

CFLAG		= -Wall -Wextra -Werror

RM			= rm -f

AR			= ar rcs

INCLUDES	= ./libft.h

all		: $(NAME)

%.o		: %.c
			$(CC) $(CFLAG) -c $< -o $@

${NAME} :	${OBJS}
			$(AR) ${NAME} ${OBJS}

clean	:
			$(RM) $(OBJS) $(OBJS_B)

fclean	:	clean
			$(RM) $(NAME)

re		: 	fclean all

$(NAME)	:	$(OBJS)
			$(AR) $@ $^

bonus	: $(OBJS) $(OBJS_B)
			$(AR) $(NAME) $^

.PHONY	: all clean fclean re
