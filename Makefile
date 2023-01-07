# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 17:36:25 by dongglee          #+#    #+#              #
#    Updated: 2023/01/07 07:52:10 by yooh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
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

SRCS =	srcs/builtin/builtin_1.c srcs/builtin/builtin_2.c srcs/builtin/builtin_3.c srcs/builtin/run_builtin.c \
		srcs/env/env.c srcs/env/env_list.c srcs/env/env_pair.c \
		srcs/etc/error.c srcs/etc/utils.c srcs/etc/utils2.c	\
		srcs/gnl/gnl_utils.c srcs/gnl/gnl.c	\
		srcs/parser/lexer.c srcs/parser/lexer_fsm.c srcs/parser/parse.c srcs/parser/token_util.c srcs/parser/validator.c srcs/parser/token_util2.c srcs/parser/parse2.c	srcs/parser/lexer_fsm2.c srcs/parser/lexer_fsm3.c\
		srcs/pipe/cmd.c srcs/pipe/pipe.c srcs/pipe/redirect.c \
		srcs/signal/signal.c	\
		srcs/main.c srcs/read.c
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
