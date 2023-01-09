/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 22:57:33 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/03 19:43:59 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init(t_global *global, const char *map_file_name)
{
	if (parse_map(global, map_file_name))
		return (1);
	// init_mlx(global);
	// init_hook(global);
	return (0);
}

void	init_mlx(t_global *global)
{
	global->mlx = mlx_init();
	global->win_ptr = mlx_new_window(global->mlx,
		global->win_size.width, global->win_size.height, "cub3d");
	global->img.ptr= mlx_new_image(global->mlx,
		global->win_size.width,
		global->win_size.height);
	global->img.ptr = mlx_get_data_addr(global->img.ptr,
		&global->img.bit_per_pixel,
		&global->img.size_line,
		&global->img.endian);
}

void	init_hook(t_global *global)
{
	mlx_loop_hook(global->mlx, &update, global);
	mlx_hook(global->win_ptr, EVENT_KEY_PRESS, MASK_PRESS, &key_press, global);
	mlx_hook(global->win_ptr, EVENT_EXIT, MASK_EXIT, &exit_game, global);
}
