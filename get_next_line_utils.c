/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:39:31 by yooh              #+#    #+#             */
/*   Updated: 2022/12/03 21:31:05 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *str)
{
	const ssize_t	length = ft_strlen(str);
	ssize_t			i;
	char			*result;

	i = -1;
	result = (char *) malloc(sizeof(char) * (length + 1));
	if (result == NULL)
		return (NULL);
	while (++i < length)
		result[i] = str[i];
	result[i] = '\0';
	return (result);
}

int	split_newline(char **left, ssize_t start, ssize_t length)
{
	ssize_t			i;
	char			*result;

	result = (char *) malloc(sizeof(char) * (length + 1));
	if (result == NULL)
		return (0);
	i = -1;
	while (++i < length)
		result[i] = (*left)[start + i];
	result[i] = '\0';
	free(*left);
	*left = result;
	return (1);
}

char	*get_until_newline(char	**left)
{
	ssize_t		i;
	ssize_t		count;
	char		*result;

	if (*left == NULL)
		return (ft_strdup(NULL));
	count = 0;
	while ((*left)[count] && (*left)[count] != '\n')
		count++;
	if (count == ft_strlen(*left))
		return (ft_strdup(NULL));
	result = (char *) malloc(sizeof(char) * (count + 2));
	if (result == NULL)
		return (NULL);
	i = -1;
	while (++i <= count)
		result[i] = (*left)[i];
	result[i] = '\0';
	if (!split_newline(left, count + 1, ft_strlen(*left) - count - 1))
	{
		free(result);
		return (NULL);
	}
	return (result);
}

char	*ft_strjoin(char **s1, char *s2, ssize_t s1_len, ssize_t s2_len)
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
