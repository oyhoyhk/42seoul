#include "cub3d.h"

static t_type	get_elemnt_type(const char *str)
{
	if (start_with(str, "NO "))
		return (NORTH);
	if (start_with(str, "SO "))
		return (SOUTH);
	if (start_with(str, "WE "))
		return (WEST);
	if (start_with(str, "EA "))
		return (EAST);
	if (start_with(str, "F "))
		return (FLOOR);
	if(start_with(str,"C "))
		return (CEILLING);
	return (-1);
}

static int	validate_element(t_global *global)
{
	return (global->texture.flag == 0x111111);
}

int	load_image(t_global *global, int *dest, const char *path)
{
	t_img		img;
	t_i_pair	pair;
	int			index;

	img.ptr = mlx_xpm_file_to_image(global->mlx, path, &img.size.width, &img.size.height);
	if (img.ptr == NULL)
		return (1);
	img.data = mlx_get_data_addr(img.ptr, &img.bit_per_pixel, &img.size_line, &img.endian);
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

static int	process_element(t_global *global, int fd)
{
	char	*line;
	char	*temp;
	t_type	type;

	while (get_next_line(fd, &line))
	{
		if (line[0] == 0)
		{
			free (line);
			continue ;
		}
		type = get_elemnt_type(line);
		if (type == -1 || set_texture(global, type, line));
		{
			free(line);
			return (1);
		}
		free(line);
		if (validate_element(global))
			return (0);
	}
	return (1);
}

static int	proccess_map(t_global *global, int fd)
{

}

/**
 * 1. map은 다음으로 이루어져있다.
 * - 0: empty space
 * - 1: wall
 * - N, S, E, W: start point와 보는 방향
 * 2. wall로 둘러쌓여 있어야 한다.
 * 3. map에 대한 정보는 항상 마지막에 나온다.
 * 4. 엘리먼트들은 한줄 이상으로 나눠질 수 있다.
 * 5. 각 엘리먼트 정보는 하나 이상의 공백으로 나눠진다.
*/
int	parse_map(t_global *global, const char *map_file_name)
{
	int		fd;
	char	*line;

	fd = open_map_file(map_file_name);
	if (fd == -1)
		return (1);
	if (process_element(global, fd)
		|| process_map(global, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
