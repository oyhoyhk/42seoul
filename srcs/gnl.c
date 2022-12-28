/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 07:32:44 by yooh              #+#    #+#             */
/*   Updated: 2022/12/11 12:34:32 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

char	*get_next_line(int fd)
{
	static char	*arr[OPEN_MAX];
	char		*result;
	char		*temp;

	temp = NULL;
	if (fd == -1)
		return (NULL);
	result = get_until_newline(&arr[fd]);
	if (result == NULL || ft_gnllen(result) > 0)
		return (result);
	free(result);
	result = read_line(arr, fd, 0, temp);
	if (result && ft_gnllen(result) == 0)
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
			result = ft_gnl_strdup(arr[fd]);
			free_fd(arr, fd);
			return (result);
		}
		arr[fd] = ft_gnljoin(&arr[fd], buf, ft_gnllen(arr[fd]), ft_gnllen(buf));
		result = get_until_newline(&arr[fd]);
		if (result == NULL && free_buf(buf))
			return (NULL);
		if (ft_gnllen(result) > 0 && free_buf(buf))
			return (result);
		free(result);
	}
}

char	*ft_gnljoin(char **s1, char *s2, ssize_t s1_len, ssize_t s2_len)
{
	const ssize_t	total_length = s1_len + s2_len;
	char			*result;
	ssize_t			i;
	ssize_t			j;

	result = (char *) malloc(sizeof(char) * (total_length + 1));
	if (result == NULL)
	{
		free(*s1);
		*s1 = NULL;
		return (NULL);
	}
	i = -1;
	while (++i < s1_len)
		result[i] = (*s1)[i];
	j = -1;
	while (++j < s2_len)
		result[i + j] = s2[j];
	result[i + j] = '\0';
	free(*s1);
	return (result);
}
