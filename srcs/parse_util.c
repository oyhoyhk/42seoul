/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:50:10 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/03 19:46:23 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_map_file(const char* map_file_name)
{
	int	fd;
	int	len;

	len = ft_strlen(map_file_name);
	if (len <= 4
		|| ft_strncmp(map_file_name + (len - 4), ".cub", 4))
		return (-1);
	fd = open(map_file_name, O_RDONLY);
	return (fd);
}

int	start_with(const char *target, const char* start)
{
	int	len;

	len = ft_strlen(start);
	return (ft_strncmp(target, start, len - 1));
}

int	get_value_index(char *line, int i)
{
	while (line[i] == ' ')
		++i;
	return (i);
}
