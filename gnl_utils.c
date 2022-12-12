/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:39:31 by yooh              #+#    #+#             */
/*   Updated: 2022/12/11 12:34:34 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

ssize_t	ft_gnllen(char *str)
{
	ssize_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_gnl_strdup(char *str)
{
	const ssize_t	length = ft_gnllen(str);
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
		return (ft_gnl_strdup(NULL));
	count = 0;
	while ((*left)[count] && (*left)[count] != '\n')
		count++;
	if (count == ft_gnllen(*left))
		return (ft_gnl_strdup(NULL));
	result = (char *) malloc(sizeof(char) * (count + 2));
	if (result == NULL)
		return (NULL);
	i = -1;
	while (++i <= count)
		result[i] = (*left)[i];
	result[i] = '\0';
	if (!split_newline(left, count + 1, ft_gnllen(*left) - count - 1))
	{
		free(result);
		return (NULL);
	}
	return (result);
}
