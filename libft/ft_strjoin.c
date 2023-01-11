/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:50:07 by yooh              #+#    #+#             */
/*   Updated: 2022/11/14 10:39:38 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	const size_t	len = ft_strlen(s1) + ft_strlen(s2);
	char			*result;
	size_t			i;
	size_t			j;

	i = -1;
	j = -1;
	result = (char *) malloc(sizeof(char) * len + 1);
	if (!result)
		return (0);
	while (s1[++i])
		result[i] = s1[i];
	while (s2[++j])
		result[i + j] = s2[j];
	result[i + j] = '\0';
	return (result);
}
