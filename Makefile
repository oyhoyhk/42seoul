SRCS	=	check_cmd_valid.c		\
			default_pipe.c			\
			ft_bzero.c				\
			ft_calloc.c				\
			ft_split.c				\
			ft_strchr.c				\
			ft_strdup.c				\
			ft_strjoin.c			\
			ft_strlen.c				\
			ft_strncmp.c			\
			ft_strtrim.c			\
			ft_substr.c				\
			parsing_path.c			\
			pipex_utils.c			\
			heredoc_bonus.c			\
			gnl.c					\
			gnl_utils.c				\

SRCS_M	=	$(SRCS)					\
			pipex.c

SRCS_B	=	$(SRCS)					\
			pipex_bonus.c

OBJS_M	=	$(SRCS_M:.c=.o)

OBJS_B	=	$(SRCS_B:.c=.o)

ifeq		($(findstring bonus, $(MAKECMDGOALS)), bonus)
			OBJS = $(OBJS_B)
else
			OBJS = $(OBJS_M)
endif

NAME	= pipex

CFLAGS	= -Wall -Wextra -Werror

all		: $(NAME)

clean	:
			$(RM) $(OBJS_M) $(OBJS_B)

fclean	:	clean
			$(RM) $(NAME)

re		:
			$(MAKE) fclean
			$(MAKE)	all

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) $^ -o $@

bonus	:	$(NAME)

.PHONY	:	all clean fclean re bonus