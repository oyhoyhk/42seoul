# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 07:54:36 by yooh              #+#    #+#              #
#    Updated: 2023/01/12 06:32:55 by yooh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	check.c init.c main.c utils.c utils2.c

OBJS			=	$(SRCS:.c=.o)

NAME			=	philo

CFLAGS			=	-Werror -Wextra -Wall 

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					$(CC) $(CFLAGS) $^ -o $@
					./philo 200 400 200 200

clean			:	$(OBJS)
					$(RM) $(OBJS);

fclean			:	clean
					$(RM) $(NAME);

re				:
					$(MAKE) fclean
					$(MAKE) all