# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 12:35:52 by yooh              #+#    #+#              #
#    Updated: 2022/11/17 08:04:21 by yooh             ###   ########.fr        #
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

SRC_B	= ft_lstnew_bonus.c			\
		  ft_lstadd_front_bonus.c	\
		  ft_lstsize_bonus.c		\
		  ft_lstlast_bonus.c		\
		  ft_lstadd_back_bonus.c	\
		  ft_lstdelone_bonus.c		\
		  ft_lstclear_bonus.c		\
		  ft_lstiter_bonus.c		\
		  ft_lstmap_bonus.c

OBJS		= $(SRC:.c=.o)

OBJS_B		= $(SRC_B:.c=.o)

NAME		= libft.a

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

AR			= ar rcs

INCLUDES	= ./libft.h

ifeq		($(findstring bonus, $(MAKECMDGOALS)), bonus)
			OBJ_SWITCH = $(OBJS) $(OBJS_B)
else
			OBJ_SWITCH = $(OBJS)
endif

all		: $(NAME)

%.o		: %.c
			$(CC) $(CFLAGS) -c $< -o $@

clean	:
			$(RM) $(OBJS) $(OBJS_B)

fclean	:	clean
			$(RM) $(NAME)

re		: 	fclean all

$(NAME)	:	$(OBJ_SWITCH)
			$(AR) $@ $^

bonus	: $(NAME)

.PHONY	:	all clean fclean re bonus
