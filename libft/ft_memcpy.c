/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:16:58 by yooh              #+#    #+#             */
/*   Updated: 2022/11/18 08:48:47 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	if (!dest && !src)
		return (NULL);
	temp = (unsigned char *) dest;
	while (i < n)
	{
		temp[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
