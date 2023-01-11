/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:19:01 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/09 18:55:01 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_game(t_global *global)
{
	(void) global;
	/* TODO: all free */
	return (0);
}

int	key_press(int key, t_global *global)
{
	/* TODO: arrow key */
	printf("%d\n", key);
	(void) global;
	// if (key == KEY_W || key == KEY_S)
	// 	move_position(global, key == KEY_W);
	// else if (key == KEY_A || key == KEY_D)
	// 	rotate_viewpoint(global, key == KEY_A);
	// else if (key == KEY_ESC)
	// 	exit_program(global);
	return (0);
}

int	update(void *global)
{
	(void) global;
	/* TODO */
	// draw_background(global);
	// raycasting(global);
	// draw(global);
	return (0);
}
