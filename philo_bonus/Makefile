# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 07:54:36 by yooh              #+#    #+#              #
#    Updated: 2023/01/12 07:49:01 by yooh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	$(wildcard *.c)

OBJS			=	$(SRCS:.c=.o)

NAME			=	philo_bonus

CFLAGS			=	-Werror -Wextra -Wall 

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					$(CC) $(CFLAGS) $^ -o $@

clean			:	$(OBJS)
					$(RM) $(OBJS);

fclean			:	clean
					$(RM) $(NAME);

re				:
					$(MAKE) fclean
					$(MAKE) all