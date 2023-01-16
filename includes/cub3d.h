/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:10:27 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/16 15:09:38 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

/* key events */
# define EVENT_EXIT 17
# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define KEY_ESC 53
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_LEFT 123
# define KEY_RIGHT 124
/* key events */

# define BLOCK_SIZE 64
# define BLOCK_AREA 4096
# define FOV 0.66
# define WIN_HEIGHT 480
# define WIN_WIDTH 640
# define ROTATION_SPEED 0.2
# define MOVE_SPEED 0.2

typedef enum e_type
{
	SOUTH,
	NORTH,
	EAST,
	WEST,
	FLOOR,
	CEILLING,
	OTHER
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

typedef struct s_kv
{
	char	*key;
	char	*value;
}	t_kv;

typedef struct s_size
{
	int	width;
	int	height;
}	t_size;

typedef struct s_img
{
	void	*ptr;
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
	int	ceilling;
	int	textures[4][BLOCK_AREA];
}	t_texture;

typedef struct s_player
{
	t_d_pair	pos;
	t_d_pair	dir;
	t_d_pair	plane;
}	t_player;

typedef struct s_global
{
	void		*mlx;
	void		*win_ptr;
	t_size		win_size;
	t_img		img;
	char		**map_ptr;
	t_size		map_size;
	t_texture	texture;
	t_player	player;
	int			buf[WIN_HEIGHT][WIN_WIDTH];
}	t_global;

typedef struct s_ray
{
	double		camera_x;
	t_d_pair	ray_dir;
	t_d_pair	side_dist;
	t_d_pair	delta_dist;
	t_i_pair	map;
	t_i_pair	step;
	int			side;
	double		prep_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;

}	t_ray;

// key_value.c
t_kv	*key_value_create(const char *key, const char *value);
void	key_value_destory(t_kv *pair);

// setting_texture.c
int		set_element(t_global *global, int type, const char *line);

// setting_map.c
int		set_map(t_global *global, t_list *lst);
int		validate_map(t_global *global);
void	set_player(t_global *global, char type, int y, int x);

// parse.c
int		set_info(t_global *global, const char *map_file_name);

// parse_util.c
int		open_map_file(const char *map_file_name);
int		start_with(const char *target, const char *start);
t_kv	*get_key_value(const char *line);

// init.c
int		init(t_global *global, const char *map_file_name);
void	init_mlx(t_global *global);
void	init_hook(t_global *global);


// update.c
int		key_press(int key, t_global *global);
int		update(t_global *global);

// gnl.c
char	*get_next_line(int fd);

// util.c
int		is_all_num(const char *str);
void	free_2d(char **strs);
int		convert_rgb(int r, int g, int b);

// draw.c
void	draw_background(t_global *global);
void	draw(t_global *global);

//raycasting.c
void	init_ray(t_global *global, t_ray *ray, int x);
void	store_texture(t_global *global, t_ray *ray, int x);
void	dda(t_global *global, t_ray *ray);
void	raycasting(t_global *global);
void	set_step_and_side_dist(t_global *global, t_ray *ray);
void	set_texture_val(t_global *global, t_ray *ray);

// exit.c
int		exit_program(t_global *global);

// player.c
void	move_position(t_global *global, int key);
void	rotate_viewpoint(t_global *global, int key);

#endif
