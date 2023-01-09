/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 08:31:40 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/02 17:41:02 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*dest_temp;
	const unsigned char	*src_temp;

	dest_temp = dest;
	src_temp = src;
	while (n--)
	{
		*dest_temp = *src_temp;
		if (*src_temp == (unsigned char)c)
			break ;
		++dest_temp;
		++src_temp;
	}
	if (*src_temp == (unsigned char)c)
		return (++dest_temp);
	return (0);
}
