CC = gcc
NAME = cub3D
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = srcs/
HEADERS_DIR = includes/

MLX_DIR = mlx/
MLX_LIB = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

FT_DIR = libft/
FT_LIB = -L$(FT_DIR) -lft

SRCS = $(wildcard $(SRC_DIR)*.c)
OBJS = $(SRCS:.c=.o)
RM = rm -f

.PHONY: all clean fclean re

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(FT_DIR) -I$(HEADERS_DIR) -c $< -o $@

$(NAME) : $(OBJS)
	make -C $(MLX_DIR)
	make -C $(FT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(FT_LIB) $(MLX_LIB)

clean :
	make -C $(MLX_DIR) clean
	make -C $(FT_DIR) clean
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all