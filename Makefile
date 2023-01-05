# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 17:36:25 by dongglee          #+#    #+#              #
#    Updated: 2023/01/05 16:45:00 by yooh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
HEADERS_DIR = includes/
SRC_DIR = srcs/
CINCLUDE = -I$(HEADERS_DIR)

RL_INCLUDE = -I${HOME}/.brew/opt/readline/include/
RL_LIB = -L${HOME}/.brew/opt/readline/lib/ -lreadline

FT_DIR = libft/
FT_INCLUDE = -I$(FT_DIR)
FT_LIB = -L$(FT_DIR) -lft

SRCS = srcs/builtin_1.c srcs/builtin_2.c srcs/builtin_3.c srcs/cmd.c srcs/env.c srcs/env_list.c srcs/env_pair.c srcs/error.c srcs/free.c srcs/gnl.c srcs/gnl_utils.c srcs/main.c srcs/parse.c srcs/parse2.c srcs/parse3.c srcs/parse_dollar.c srcs/pipe.c srcs/read.c srcs/redirect.c srcs/run_builtin.c srcs/signal.c srcs/tokenize.c srcs/utils.c srcs/parse4.c srcs/utils2.c
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