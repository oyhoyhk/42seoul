/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leedonggyu <leedonggyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 20:31:01 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/01 11:06:39 by leedonggyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t dest_len;
	size_t src_len;
	size_t i;
	size_t j;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	j = dest_len;
	if (size != 0 && (size - 1) > dest_len)
	{
		while (src[i] && (size - 1) > (dest_len + i))
			dest[j++] = src[i++];
		dest[j] = '\0';
	}
	if (size <= dest_len)
		return (src_len + size);
	else
		return (src_len + dest_len);
}
