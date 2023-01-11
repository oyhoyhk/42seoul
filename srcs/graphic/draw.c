/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:54:11 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/11 13:22:07 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_global *global)
{
	int x;
	int y;

	y = 0;
	while (y < global->win_size.height)
	{
		x = 0;
		while (x < global->win_size.width)
		{
			if (y < global->win_size.height / 2)
				global->buf[y][x] = global->texture.ceilling;
			else
				global->buf[y][x] = global->texture.floor;
			++x;
		}
		++y;
	}
}

void	draw(t_global *global)
{
	int x;
	int y;

	y = 0;
	while (y < global->win_size.height)
	{
		x = 0;
		while (x < global->win_size.width)
		{
			global->img.data[y * global->win_size.width + x] = global->buf[y][x];
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(global->mlx, global->win_ptr, global->img.ptr, 0, 0);
}
