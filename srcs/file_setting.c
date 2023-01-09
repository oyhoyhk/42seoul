/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_setting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:48:00 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/03 19:48:29 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_wall_texture(t_global *global, int type, char *line)
{
	char	*path;

	path = ft_strtrim(line, " ");
	if (load_image(global, global->texture.textures[type], path))
	{
		free(path);
		return (1);
	}
	free(path);
}

int	set_background_color(t_global *global, int type, char *line)
{
	char	*raw;
	char	**rgb;
	int		i;
	int		temp;
	int		rst;

	raw = ft_strtrim(line, " ");
	rgb = ft_split(raw, ',');
	i = 0;
	rst = 0;
	free(raw);
}

int	set_texture(t_global *global, int type, char *line)
{
	int	i;
	int	len;
	int	temp;

	if (global->texture.flag & (1 << type))
		return (1);
	len = ft_strlen(line);
	if (type == NORTH || type == SOUTH || type == EAST || type == WEST)
	{
		i = get_value_index(line, 2);
		temp = ft_substr(line, i, len - i);
		if (set_wall_texture(global, type, temp))
			return (1);
		free(temp);
	}
	else if (type == FLOOR || type == CEILLING)
	{
		i = get_value_index(line, 1);
		temp = ft_substr(line, i, len - i);
		if (set_background_color(global, type, temp))
			return (1);
		free(temp);
	}
	global->texture.flag |= (1 << type);
	return (0);
}
