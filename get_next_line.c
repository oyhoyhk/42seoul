/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 07:32:44 by yooh              #+#    #+#             */
/*   Updated: 2022/12/03 21:56:41 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*arr[OPEN_MAX];
	char		*result;
	char		*temp;

	temp = NULL;
	if (fd == -1)
		return (NULL);
	result = get_until_newline(&arr[fd]);
	if (result == NULL || ft_strlen(result) > 0)
		return (result);
	free(result);
	result = read_line(arr, fd, 0, temp);
	if (result && ft_strlen(result) == 0)
	{
		free (result);
		return (NULL);
	}
	return (result);
}

int	free_buf(char *buf)
{
	free(buf);
	return (1);
}

int	free_fd(char **arr, int fd)
{
	if (arr[fd])
		free(arr[fd]);
	arr[fd] = NULL;
	return (1);
}

char	*read_line(char **arr, int fd, ssize_t read_count, char *result)
{
	char	*buf;

	buf = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL && free_fd(arr, fd))
		return (NULL);
	while (1)
	{
		read_count = read(fd, buf, BUFFER_SIZE);
		if (read_count == -1 && free_buf(buf) && free_fd(arr, fd))
			return (NULL);
		buf[read_count] = '\0';
		if (read_count == 0 && free_buf(buf))
		{
			result = ft_strdup(arr[fd]);
			free_fd(arr, fd);
			return (result);
		}
		arr[fd] = ft_strjoin(&arr[fd], buf, ft_strlen(arr[fd]), ft_strlen(buf));
		result = get_until_newline(&arr[fd]);
		if (result == NULL && free_buf(buf))
			return (NULL);
		if (ft_strlen(result) > 0 && free_buf(buf))
			return (result);
		free(result);
	}
}

ssize_t	ft_strlen(char *str)
{
	ssize_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
