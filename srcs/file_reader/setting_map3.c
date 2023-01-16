/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_map3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:25:16 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/16 21:29:01 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_void_space(t_global *global, int y, int x)
{
	return (y < 0 || y >= global->map_size.height
		|| x < 0 || x >= global->map_size.width
		|| (global->map_ptr[y][x] != '0' && global->map_ptr[y][x] != '1'));
}

int	validate_map(t_global *global)
{
	const int	dx[8] = {1, 0, -1, 0, 1, -1, -1, 1};
	const int	dy[8] = {0, -1, 0, 1, -1, -1, 1, 1};
	int			y;
	int			x;
	int			i;

	y = -1;
	while (++y < global->map_size.height)
	{
		x = -1;
		while (++x < global->map_size.width)
		{
			if (global->map_ptr[y][x] == '0')
			{
				i = -1;
				while (++i < 8)
				{
					if (is_void_space(global, y + dy[i], x + dx[i]))
						return (1);
				}
			}
		}
	}
	return (0);
}

int	set_map_line(t_global *global, char *str, t_i_pair *pair, int *flag)
{
	if (str[0] == '\n')
		return (2);
	pair->x = 0;
	while (str[pair->x] && str[pair->x] != '\n')
	{
		if (str[pair->x] == ' ' || str[pair->x] == '0'
			|| str[pair->x] == '1')
			global->map_ptr[pair->y][pair->x] = str[pair->x];
		else if (str[pair->x] == 'N' || str[pair->x] == 'S'
			|| str[pair->x] == 'E' || str[pair->x] == 'W')
		{
			if (*flag)
				return (1);
			*flag = 1;
			global->map_ptr[pair->y][pair->x] = '0';
			set_player(global, str[pair->x], *pair);
		}
		else
			return (1);
		++pair->x;
	}
	return (0);
}

void	fill_map_emt(t_global *global, t_i_pair *pair)
{
	while (pair->x < global->map_size.width)
	{
		global->map_ptr[pair->y][pair->x] = ' ';
		++pair->x;
	}
}

int	set_map_emt(t_global *global, t_list *lst)
{
	t_list		*cur;
	t_i_pair	pair;
	int			flag;
	int			rst;

	cur = lst;
	flag = 0;
	pair.y = 0;
	while (cur)
	{
		rst = set_map_line(global, (char *)cur->content, &pair, &flag);
		if (rst == 1)
			return (1);
		else if (rst == 2)
			break ;
		fill_map_emt(global, &pair);
		cur = cur->next;
		++pair.y;
	}
	return (!flag);
}
