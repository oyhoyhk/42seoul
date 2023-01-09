/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donggyulee <donggyulee@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 10:45:44 by dongglee          #+#    #+#             */
/*   Updated: 2020/08/24 21:58:06 by donggyulee       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strcpy(char *dest, char *src)
{
	if (!dest || !src)
		return ;
	while (*src)
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = '\0';
}

char	*ft_strdup(char *src)
{
	int		len;
	char	*ret;

	len = 0;
	while (src[len])
		++len;
	ret = malloc(sizeof(char) * (len + 1));
	if (ret == 0)
		return (ret);
	len = 0;
	while (src[len])
	{
		ret[len] = src[len];
		++len;
	}
	ret[len] = '\0';
	return (ret);
}

int		err_flag(char **line)
{
	free(*line);
	*line = NULL;
	return (R_ERROR);
}

int		get_next_line(int fd, char **line)
{
	static char	fd_buff[OPEN_MAX][BUFFER_SIZE + 1];
	char		buff[BUFFER_SIZE + 1];
	int			read_cnt;
	int			eof_flag;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || !(*line = ft_strdup("")))
		return (R_ERROR);
	eof_flag = R_EOF;
	if (fd_buff[fd][0] && (eof_flag = make_line(line, fd_buff[fd])) != R_EOF)
		return (eof_flag);
	while ((read_cnt = read(fd, buff, BUFFER_SIZE)))
	{
		if (read_cnt < 0)
			return (err_flag(line));
		buff[read_cnt] = '\0';
		if ((eof_flag = make_line(line, buff)) == R_ERROR)
			return (R_ERROR);
		if (eof_flag == R_SUCCESS)
		{
			ft_strcpy(fd_buff[fd], buff);
			break ;
		}
	}
	return (eof_flag);
}
