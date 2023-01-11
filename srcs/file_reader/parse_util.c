/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:50:10 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/10 14:26:15 by dongglee         ###   ########.fr       */
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
	return (!ft_strncmp(target, start, len - 1));
}

t_kv	*get_key_value(const char *line)
{
	int		i;
	t_kv	*ret;
	int		len;
	char	*key;
	char	*value;

	i = 0;
	len = ft_strlen(line);
	while (line[i] && line[i] != ' ')
		++i;
	if (line[i] == '\0')
		return (NULL);
	key = ft_substr(line, 0, i);
	while (line[i] && line[i] == ' ')
		++i;
	if (i == len)
	{
		free(key);
		return (NULL);
	}
	value = ft_substr(line, i, len - i - 1);
	ret = key_value_create(key, value);
	free(key);
	free(value);
	return (ret);
}
