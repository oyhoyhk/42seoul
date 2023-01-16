/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:34:48 by yooh              #+#    #+#             */
/*   Updated: 2023/01/16 15:00:26 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_global *global)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < global->win_size.width)
	{
		init_ray(global, &ray, x);
		set_step_and_side_dist(global, &ray);
		dda(global, &ray);
		set_texture_val(global, &ray);
		store_texture(global, &ray, x);
		++x;
	}
}

void	set_texture_val(t_global *global, t_ray *ray)
{
	if (ray->side == EAST || ray->side == WEST)
		ray->prep_wall_dist = (ray->map.x - global->player.pos.x
				+ (1 - ray->step.x) / 2) / ray->ray_dir.x;
	else
		ray->prep_wall_dist = (ray->map.y - global->player.pos.y
				+ (1 - ray->step.y) / 2) / ray->ray_dir.y;
	ray->line_height = (int)(global->win_size.height / ray->prep_wall_dist);
	ray->draw_start = -ray->line_height / 2 + global->win_size.height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + global->win_size.height / 2;
	if (ray->draw_end >= global->win_size.height)
		ray->draw_end = global->win_size.height - 1;
}

void	set_step_and_side_dist(t_global *global, t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (global->player.pos.x - ray->map.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - global->player.pos.x)
			* ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (global->player.pos.y - ray->map.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - global->player.pos.y)
			* ray->delta_dist.y;
	}
}
