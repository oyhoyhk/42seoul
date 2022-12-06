/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:57:53 by yooh              #+#    #+#             */
/*   Updated: 2022/12/05 20:37:31 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include "deque.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <string.h>

# include <stdio.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_pos
{
	int		xpos;
	int		ypos;
}	t_pos;

typedef struct s_size_info
{
	ssize_t	width;
	ssize_t	height;
}	t_size_info;

typedef struct s_trap_info
{
	int		x;
	int		y;
}	t_trap_info;

typedef struct s_images
{
	void	*wall;
	void	*player_1;
	void	*player_2;
	void	*player_3;
	void	*trap;
	void	*present_1;
	void	*present_2;
	void	*goal;
}	t_images;

typedef struct s_game_info
{
	int			cur_x;
	int			cur_y;
	int			present_count;
	int			total_present;
	int			move_count;
	int			game_over;
	int			traps_count;
	int			player_count;
	int			goal_count;
	t_deque		*traps;
}	t_game_info;

typedef struct s_mlx_info
{
	void				*mlx;
	void				*win;
	char				**board;
	t_size_info			size_info;
	struct s_game_info	game_info;
	struct s_images		images;
}	t_mlx_info;

typedef struct s_count_info
{
	int		player;
	int		present;
}	t_count_info;

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_ESC 53

# define WALL		"img/wall.xpm"
# define PLAYER		"img/player.xpm"
# define TRAP		"img/trap.xpm"
# define PRESENT	"img/present.xpm"
# define GOAL		"img/goal.xpm"

enum e_ERROR
{
	EIO,
	EBADF,
	ENOMEM
};

t_size_info		cal_window_size(char **board);
void			create_window(t_mlx_info *game);
t_deque			*parse_file_to_deque(char *name);
int				get_rand_dir(void);
void			input_valid_check(t_mlx_info *game);
char			**parse_deque_to_arr(t_deque *dq);
void			set_mlx_info(t_mlx_info *game, char *filename);
void			draw_imgs(t_mlx_info game);
void			draw_bg(t_mlx_info game);
int				key_event(int keycode, t_mlx_info *game);
void			set_player_position(t_mlx_info *game);
void			draw_imgs(t_mlx_info game);
char			*ft_itoa(int n);
void			game_over_win(t_mlx_info game);
void			game_over_lose(t_mlx_info game);
char			*get_present_url(int *present);
char			*get_player_url(int *player);
void			patrol_trap(t_mlx_info *game);
void			escape_check(t_mlx_info *game);
void			perror_and_exit(int err);
void			ft_bzero(void *s, size_t n);
void			set_images(t_images *images, t_mlx_info *game);
void			free_visited(int **visited, char **board);

#endif