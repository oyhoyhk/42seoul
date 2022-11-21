/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:35:26 by yooh              #+#    #+#             */
/*   Updated: 2022/11/18 08:48:57 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*temp;
	unsigned char	*source;

	temp = (unsigned char *) dest;
	source = (unsigned char *) src;
	if (!dest && !src)
		return (NULL);
	if (dest <= src)
		while (n--)
			*temp++ = *source++;
	else
	{
		temp += n;
		source += n;
		while (n--)
			*(--temp) = *(--source);
	}
	return (dest);
}
