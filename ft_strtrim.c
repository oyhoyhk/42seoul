/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 07:28:04 by yooh              #+#    #+#             */
/*   Updated: 2022/11/15 14:17:20 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	has_char(char ch, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	left;
	size_t	right;

	if (!s1 || !set)
		return (NULL);
	if (!ft_strlen(s1))
		return (ft_calloc(1, 1));
	if (!ft_strlen(set))
		return (ft_strdup(s1));
	left = 0;
	right = ft_strlen(s1) - 1;
	while (has_char(s1[left], set))
		left++;
	while (right > 0 && has_char(s1[right], set))
		right--;
	if (left > right)
		return (ft_calloc(1, 1));
	return (ft_substr(s1, left, right - left + 1));
}
