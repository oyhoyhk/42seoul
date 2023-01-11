/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:51:12 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/12 13:13:03 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_global *global, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)global->win_size.width - 1;
	ray->ray_dir.x = global->player.dir.x + global->player.plane.x * ray->camera_x;
	ray->ray_dir.y = global->player.dir.y + global->player.plane.y * ray->camera_x;
	ray->map.x = (int)global->player.pos.x;
	ray->map.y = (int)global->player.pos.y;
	ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
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

void	dda(t_global *global, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			if (ray->step.x == -1)
				ray->side = EAST;
			else
				ray->side = WEST;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			if (ray->step.y == -1)
				ray->side = NORTH;
			else
				ray->side = SOUTH;
		}
		if (global->map_ptr[ray->map.y][ray->map.x] == '1')
			hit = 1;
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

void	store_texture(t_global *global, t_ray *ray, int x)
{
	double		wall_x;
	t_i_pair	tex;
	double		step;
	double		tex_pos;
	int			y;

	if (ray->side == EAST || ray->side == WEST)
		wall_x = (global->player.pos.y + ray->prep_wall_dist * ray->ray_dir.y);
	else
		wall_x = (global->player.pos.x + ray->prep_wall_dist * ray->ray_dir.x);
	wall_x -= floor(wall_x);
	tex.x = (int)(wall_x * (double)BLOCK_SIZE);
	if (((ray->side == EAST || ray->side == WEST) && ray->ray_dir.x > 0)
		|| ((ray->side == SOUTH || ray->side == NORTH) && ray->ray_dir.y < 0))
		tex.x = BLOCK_SIZE - tex.x - 1;
	step = 1.0 * BLOCK_SIZE / ray->line_height;
	tex_pos = (ray->draw_start - global->win_size.height
		/ 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex.y = (int)tex_pos & (BLOCK_SIZE - 1);
		tex_pos += step;
		global->buf[y][x] = global->texture.textures[ray->side][BLOCK_SIZE * tex.y + tex.x];
		++y;
	}
}

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
