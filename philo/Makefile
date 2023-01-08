# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 07:54:36 by yooh              #+#    #+#              #
#    Updated: 2023/01/08 11:10:44 by yooh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	$(wildcard *.c)

OBJS			=	$(SRCS:.c=.o)

NAME			=	philo

CFLAGS			=	-Werror -Wextra -Wall

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					$(CC) $(CFLAGS) $^ -o $@ 
					./$(NAME) 5 500 200 200

clean			:	$(OBJS)
					$(RM) $(OBJS);

fclean			:	clean
					$(RM) $(NAME);

re				:
					$(MAKE) fclean
					$(MAKE) all