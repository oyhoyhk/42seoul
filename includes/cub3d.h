/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:10:27 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/03 22:37:35 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

/* key events */
# define EVENT_EXIT 17
# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define MASK_PRESS 0
# define MASK_RELEASE 0
# define MASK_EXIT 0
# define KEY_ESC 53
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
#
/* key events */

# define BLOCK_SIZE 64
# define BLOCK_AREA 4046

typedef enum e_type
{
	SOUTH, NORTH, EAST, WEST, FLOOR, CEILLING
}	t_type;

typedef struct s_d_pair
{
	double	x;
	double	y;
}	t_d_pair;

typedef struct s_i_pair
{
	int	x;
	int	y;
}	t_i_pair;

typedef struct s_size
{
	int	width;
	int	height;
}	t_size;;

typedef struct	s_img
{
	char	*ptr;
	int		*data;
	int		bit_per_pixel;
	int		size_line;
	int		endian;
	t_size	size;
}	t_img;

typedef struct s_texture
{
	int	flag;
	int	floor;
	int	celling;
	int	textures[4][BLOCK_AREA];
}	t_texture;


typedef struct s_global
{
	void		*mlx;
	void		*win_ptr;
	t_size		win_size;
	t_img		img;
	char		**map_ptr;
	t_size		map_size;
	t_texture	texture;
}	t_global;

// parse.c
int	parse_map(t_global *global, const char *map_file_name);

// parse_util.c
int	open_map_file(const char* map_file_name);
int	start_with(const char *target, const char* start);
int	get_value_index(char *line, int i);

// init.c
int		init(t_global *global, const char *map_file_name);
void	init_mlx(t_global *global);
void	init_hook(t_global *global);

//

// update.c
int		key_press(int key, t_global *global);
int		exit_game(t_global global);
int		update(void *global);

#endif
