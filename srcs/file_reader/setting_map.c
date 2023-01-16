/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:58:29 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/16 21:10:25 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_map_size(t_global *global, t_list *lst)
{
	t_list	*cur;
	char	*temp;
	int		len;

	cur = lst;
	while (cur)
	{
		temp = (char *)cur->content;
		if (temp[0] == '\n')
			break ;
		global->map_size.height++;
		len = ft_strlen(temp) - 1;
		if (len > global->map_size.width)
			global->map_size.width = len;
		cur = cur->next;
	}
}

int	set_map_emt(t_global *global, t_list *lst)
{
	t_list		*cur;
	t_i_pair	pair;
	char		*temp;
	int			flag;

	cur = lst;
	flag = 0;
	pair.y = 0;
	while (cur)
	{
		temp = (char *) cur->content;
		if (temp[0] == '\n')
			break ;
		pair.x = 0;
		while (temp[pair.x] && temp[pair.x] != '\n')
		{
			if (temp[pair.x] == ' ')
				global->map_ptr[pair.y][pair.x] = ' ';
			else if (temp[pair.x] == '0')
				global->map_ptr[pair.y][pair.x] = '0';
			else if (temp[pair.x] == '1')
				global->map_ptr[pair.y][pair.x] = '1';
			else if (temp[pair.x] == 'N' || temp[pair.x] == 'S'
				|| temp[pair.x] == 'E' || temp[pair.x] == 'W')
			{
				if (flag)
					return (1);
				flag = 1;
				global->map_ptr[pair.y][pair.x] = '0';
				set_player(global, temp[pair.x], pair);
			}
			else
				return (1);
			++pair.x;
		}
		while (pair.x < global->map_size.width)
		{
			global->map_ptr[pair.y][pair.x] = ' ';
			++pair.x;
		}
		cur = cur->next;
		++pair.y;
	}
	return (!flag);
}

t_list	*skip_empty_line(t_list *cur)
{
	char	*temp;

	temp = (char *)cur->content;
	while (cur && temp[0] == '\n')
	{
		cur = cur->next;
		if (cur == NULL)
			break ;
		temp = (char *)cur->content;
	}
	return (cur);
}

int	set_map(t_global *global, t_list *lst)
{
	t_list	*cur;
	int		i;

	cur = skip_empty_line(lst);
	if (cur == NULL)
		return (1);
	set_map_size(global, cur);
	global->map_ptr = malloc(sizeof(char *) * (global->map_size.height + 1));
	global->map_ptr[global->map_size.height] = NULL;
	i = -1;
	while (++i < global->map_size.height)
		global->map_ptr[i] = malloc(sizeof(char) * global->map_size.width);
	if (set_map_emt(global, cur))
	{
		free_2d(global->map_ptr);
		return (1);
	}
	return (0);
}

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
