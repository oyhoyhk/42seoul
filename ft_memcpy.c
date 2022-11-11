/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:16:58 by yooh              #+#    #+#             */
/*   Updated: 2022/11/10 11:15:23 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *restrict dest, const void *restrict src, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	if (!src && !dest)
		return (0);
	i = 0;
	temp = (unsigned char *) dest;
	while (i < n)
	{
		temp[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
