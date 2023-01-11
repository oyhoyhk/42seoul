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
	return (OTHER);
}

static int	validate_element(t_global *global)
{
	return (global->texture.flag == 0x3f);
}

static int	process_element(t_global *global, int fd)
{
	char	*line;
	t_type	type;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != 0 && line[0] != '\n')
		{
			type = get_elemnt_type(line);
			if (type == OTHER || set_element(global, type, line))
			{
				free(line);
				return (1);
			}
			free(line);
		}
		if (validate_element(global))
			return (0);
		line = get_next_line(fd);
	}
	return (1);
}

static int	process_map(t_global *global, int fd)
{
	t_list	*lst;
	char	*line;

	lst = NULL;
	line = get_next_line(fd);
	while (line)
	{
		ft_lstadd_back(&lst, ft_lstnew(line));
		line = get_next_line(fd);
	}
	if (set_map(global, lst))
	{
		ft_lstclear(&lst, free);
		return (1);
	}
	ft_lstclear(&lst, free);
	if (validate_map(global))
	{
		free_2d(global->map_ptr);
		return (1);
	}
	return (0);
}

int	set_info(t_global *global, const char *map_file_name)
{
	int		fd;

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
