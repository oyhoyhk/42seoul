/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:48:00 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/10 22:36:21 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_image(t_global *global, int *dest, char *path)
{
	t_img		img;
	t_i_pair	pair;
	int			index;
	int			len;

	len = ft_strlen(path);
	ft_memset(&img, 0, sizeof(img));
	if (!ft_strncmp(path + (len - 4), ".xpm", 4))
		img.ptr = mlx_xpm_file_to_image(global->mlx, path, &img.size.width, &img.size.height);
	if (img.ptr == NULL)
		return (1);
	img.data = (int *)mlx_get_data_addr(img.ptr, &img.bit_per_pixel, &img.size_line, &img.endian);
	pair.y = 0;
	while (pair.y < img.size.height)
	{
		pair.x = 0;
		while (pair.x < img.size.width)
		{
			index = img.size.width * pair.y + pair.x;
			dest[index] = img.data[index];
			++pair.x;
		}
		++pair.y;
	}
	return (0);
}

static int	set_wall_texture(t_global *global, int type, t_kv *kv)
{
	if (load_image(global, global->texture.textures[type], kv->value))
		return (1);
	return (0);
}

static int	set_background_color(t_global *global, int type, t_kv *kv)
{
	char	**rgb;
	int		irgb[3];
	int		i;

	rgb = ft_split(kv->value, ',');
	i = 0;
	while (rgb[i])
	{
		if (i >=3 || !is_all_num(rgb[i]))
		{
			free_2d(rgb);
			return (1);
		}
		irgb[i] = ft_atoi(rgb[i]);
		if (irgb[i] > 255)
		{
			free_2d(rgb);
			return (1);
		}
		++i;
	}
	free_2d(rgb);
	if (type == FLOOR)
		global->texture.floor = convert_rgb(irgb[0], irgb[1], irgb[2]);
	else if (type == CEILLING)
		global->texture.ceilling = convert_rgb(irgb[0], irgb[1], irgb[2]);
	return (0);
}

int	set_element(t_global *global, int type, const char *line)
{
	t_kv	*key_value;

	if (global->texture.flag & (1 << type))
		return (1);
	key_value = get_key_value(line);
	if (key_value == NULL)
		return (1);
	if (((type == NORTH || type == SOUTH || type == EAST || type == WEST)
			&& set_wall_texture(global, type, key_value))
		|| ((type == FLOOR || type == CEILLING)
			&& set_background_color(global, type, key_value)))
	{
		key_value_destory(key_value);
		return (1);
	}
	global->texture.flag |= (1 << type);
	return (0);
}
