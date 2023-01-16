/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 22:57:33 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/16 14:19:59 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init(t_global *global, const char *map_file_name)
{
	global->win_size.height = WIN_HEIGHT;
	global->win_size.width = WIN_WIDTH;
	init_mlx(global);
	if (set_info(global, map_file_name))
		return (1);
	init_hook(global);
	return (0);
}

void	init_mlx(t_global *global)
{
	global->mlx = mlx_init();
	global->win_ptr = mlx_new_window(global->mlx,
			global->win_size.width, global->win_size.height, "cub3d");
	global->img.ptr = mlx_new_image(global->mlx,
			global->win_size.width,
			global->win_size.height);
	global->img.data = (int *)mlx_get_data_addr(global->img.ptr,
			&global->img.bit_per_pixel,
			&global->img.size_line,
			&global->img.endian);
}

void	init_hook(t_global *global)
{
	mlx_loop_hook(global->mlx, update, global);
	mlx_hook(global->win_ptr, EVENT_KEY_PRESS, 0, key_press, global);
	mlx_hook(global->win_ptr, EVENT_EXIT, 0, exit_program, global);
}
