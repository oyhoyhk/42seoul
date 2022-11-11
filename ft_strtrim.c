/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 07:28:04 by yooh              #+#    #+#             */
/*   Updated: 2022/11/11 12:07:42 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	has_char(char ch, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

char	*create_empty_string(void)
{
	char	*result;

	result = (char *) malloc(sizeof(char) * 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	return (result);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	left;
	int	right;

	if (!s1 || !set)
		return (NULL);
	if (!ft_strlen(s1))
		return (create_empty_string());
	if (!ft_strlen(set))
		return (ft_strdup(s1));
	left = 0;
	right = ft_strlen(s1) - 1;
	while (has_char(s1[left], set))
		left++;
	while (has_char(s1[right], set))
		right--;
	if (left > right)
		return (create_empty_string());
	return (ft_substr(s1, left, right - left + 1));
}
