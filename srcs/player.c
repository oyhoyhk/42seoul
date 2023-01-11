/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:29:17 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/11 21:25:04 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_position(t_global *global, int key)
{
	double	y;
	double	x;

	if (key == KEY_W)
	{
		y = global->player.pos.y + global->player.dir.y * MOVE_SPEED;
		x = global->player.pos.x + global->player.dir.x * MOVE_SPEED;
	}
	else if (key == KEY_A)
	{
		y = global->player.pos.y + global->player.dir.x * MOVE_SPEED;
		x = global->player.pos.x - global->player.dir.y * MOVE_SPEED;
	}
	else if (key == KEY_D)
	{
		y = global->player.pos.y - global->player.dir.x * MOVE_SPEED;
		x = global->player.pos.x + global->player.dir.y * MOVE_SPEED;
	}
	else if (key == KEY_S)
	{
		y = global->player.pos.y - global->player.dir.y * MOVE_SPEED;
		x = global->player.pos.x - global->player.dir.x * MOVE_SPEED;
	}
	else
		return ;
	if (global->map_ptr[(int)global->player.pos.y][(int)x] == '0')
		global->player.pos.x = x;
	if (global->map_ptr[(int)y][(int)global->player.pos.x] == '0')
		global->player.pos.y = y;
}

void rotate_viewpoint(t_global *global, int key)
{
	double	temp;
	int		opt;

	if (key == KEY_LEFT)
		opt = 1;
	else
		opt = -1;
	temp = global->player.dir.x;
	global->player.dir.x = global->player.dir.x * cos(opt * ROTATION_SPEED)
		- global->player.dir.y * sin(opt * ROTATION_SPEED);
	global->player.dir.y = temp * sin(opt * ROTATION_SPEED)
		+ global->player.dir.y * cos(opt * ROTATION_SPEED);
	temp = global->player.plane.x;
	global->player.plane.x = global->player.plane.x * cos(opt * ROTATION_SPEED)
		- global->player.plane.y * sin(opt * ROTATION_SPEED);
	global->player.plane.y = temp * sin(opt * ROTATION_SPEED)
		+ global->player.plane.y * cos(opt * ROTATION_SPEED);
}
