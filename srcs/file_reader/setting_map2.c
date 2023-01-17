/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:08:53 by yooh              #+#    #+#             */
/*   Updated: 2023/01/17 17:28:30 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ps_y_axis(t_global *global, char type)
{
	global->player.plane.x = 0;
	global->player.dir.y = 0;
	if (type == 'N')
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

static void	ps_x_axis(t_global *global, char type)
{
	global->player.plane.y = 0;
	global->player.dir.x = 0;
	if (type == 'E')
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

void	set_player(t_global *global, char type, t_i_pair pair)
{
	global->player.pos.y = pair.y;
	global->player.pos.x = pair.x;
	if (type == 'N' || type == 'S')
		ps_y_axis(global, type);
	else if (type == 'E' || type == 'W')
		ps_x_axis(global, type);
}
