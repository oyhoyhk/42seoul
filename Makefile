# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 17:36:25 by dongglee          #+#    #+#              #
#    Updated: 2022/12/31 15:30:00 by dongglee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g # g옵션 나중에 빼야함ㅡㅁ
HEADERS_DIR = includes/
SRC_DIR = srcs/
CINCLUDE = -I$(HEADERS_DIR)

 #42seoul
RL_INCLUDE = -I${HOME}/.brew/opt/readline/include/
RL_LIB = -L${HOME}/.brew/opt/readline/lib/ -lreadline

## my mac
#RL_INCLUDE = -I/opt/homebrew/opt/readline/include/
#RL_LIB = -L/opt/homebrew/opt/readline/lib/ -lreadline

FT_DIR = libft/
FT_INCLUDE = -I$(FT_DIR)
FT_LIB = -L$(FT_DIR) -lft

# wildcard 나중에 바꿔야함!
SRCS = $(wildcard $(SRC_DIR)*.c)
OBJS = $(SRCS:.c=.o)
RM = rm -f

.PHONY: all clean fclean re

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(CINCLUDE) $(RL_INCLUDE) $(FT_INCLUDE) -c $< -o $@

$(NAME) : $(OBJS)
	$(MAKE) bonus -C $(FT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(RL_LIB) $(FT_LIB)

clean :
	$(MAKE) -C $(FT_DIR) clean
	$(RM) $(OBJS)

fclean : clean
	$(MAKE) -C $(FT_DIR) fclean
	$(RM) $(NAME)

re : fclean all

# for test
test: $(OBJS) test.c
	$(CC) $(CFLAGS) $(CINCLUDE) $(RL_INCLUDE) $(FT_INCLUDE) -c test.c -o test.o
	$(MAKE) -C $(FT_DIR) bonus
	$(CC) $(CFLAGS) -o test $(filter-out %/main.o,$(OBJS)) test.o $(RL_LIB) $(FT_LIB)
tclean: fclean
	$(RM) test test.o

tmpclean:
	$(RM) *.tmp