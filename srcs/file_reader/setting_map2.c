/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:08:53 by yooh              #+#    #+#             */
/*   Updated: 2023/01/16 17:38:56 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_y_axis(t_global *global, char type)
{
	global->player.plane.x = 0;
	global->player.dir.y = 0;
	if (type == 'N')
	{
		global->player.plane.y = FOV;
		global->player.dir.x = -1;
	}
	else
	{
		global->player.plane.y = -FOV;
		global->player.dir.x = 1;
	}
}

static void	handle_x_axis(t_global *global, char type)
{
	global->player.plane.y = 0;
	global->player.dir.x = 0;
	if (type == 'E')
	{
		global->player.plane.x = FOV;
		global->player.dir.y = 1;
	}
	else
	{
		global->player.plane.x = -FOV;
		global->player.dir.y = -1;
	}
}

void	set_player(t_global *global, char type, int y, int x)
{
	global->player.pos.y = y;
	global->player.pos.x = x;
	if (type == 'N' || type == 'S')
		handle_y_axis(global, type);
	else if (type == 'E' || type == 'W')
		handle_x_axis(global, type);
}
