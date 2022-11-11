/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 08:21:05 by yooh              #+#    #+#             */
/*   Updated: 2022/11/10 11:43:55 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	**allocate_double_ptr_result(int has_last, int count)
{
	char	**result;

	if (has_last)
		result = (char **) malloc(sizeof(char *) * (count + 2));
	else
		result = (char **) malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	return (result);
}

void	put_str_in_result(char *str, int i, int count, char **result)
{
	if (i != 0)
	{
		result[count + 1] = NULL;
		result[count] = ft_substr(str, 0, i);
	}
	else
		result[count] = NULL;
}

char	**recursive(char *str, char delimiter, int count)
{
	int		i;
	char	**result;

	i = 0;
	while (str[i] != delimiter && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		result = allocate_double_ptr_result(i, count);
		if (!result)
			return (NULL);
		put_str_in_result(str, i, count, result);
		return (result);
	}
	if (i == 0)
		return (recursive(str + 1, delimiter, count));
	result = recursive(str + i + 1, delimiter, count + 1);
	if (!result)
		return (NULL);
	result[count] = ft_substr(str, 0, i);
	if (!result[count])
		return (NULL);
	return (result);
}

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (recursive((char *)s, c, 0));
}
