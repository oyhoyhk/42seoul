/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leedonggyu <leedonggyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 21:19:08 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/26 17:25:15 by leedonggyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t i;
	size_t j;

	if (find[0] == '\0')
		return ((char *)str);
	if (len == 0)
		return (NULL);
	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] && find[j] && i + j < len)
		{
			if (str[i + j] != find[j])
				break ;
			++j;
		}
		if (!find[j])
			return ((char *)&str[i]);
		++i;
	}
	return (0);
}
