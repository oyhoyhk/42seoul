/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donggyulee <donggyulee@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 11:51:29 by dongglee          #+#    #+#             */
/*   Updated: 2020/08/24 21:58:00 by donggyulee       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t n;

	n = 0;
	while (s[n])
		++n;
	return (n);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!ret)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[j])
		ret[i++] = s1[j++];
	j = 0;
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_temp;
	const char	*src_temp;
	int			flag;

	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		dest_temp = dest;
		src_temp = src;
		flag = 1;
	}
	else
	{
		dest_temp = dest + n - 1;
		src_temp = src + n - 1;
		flag = -1;
	}
	while (n--)
	{
		*dest_temp = *src_temp;
		dest_temp += flag;
		src_temp += flag;
	}
	return (dest);
}

int		make_line(char **line, char *buff)
{
	int		buff_len;
	int		i;
	int		flag;
	char	*temp;

	if (!buff)
		return (R_EOF);
	buff_len = ft_strlen(buff);
	i = 0;
	while (buff[i] && buff[i] != '\n')
		++i;
	flag = (buff[i] == '\n');
	buff[i] = '\0';
	if (!(temp = ft_strjoin(*line, buff)))
		return (R_ERROR);
	if (buff_len == i)
		buff[0] = '\0';
	else
		ft_memmove(buff, &buff[i + 1], buff_len - i);
	free(*line);
	*line = temp;
	if (flag)
		return (R_SUCCESS);
	return (R_EOF);
}
