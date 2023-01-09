/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 08:46:19 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/02 17:33:34 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_temp;
	const char	*src_temp;
	int			flag;

	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		dest_temp = dest;
		src_temp = src;
		flag = 1;
	}
	else
	{
		dest_temp = dest + n - 1;
		src_temp = src + n - 1;
		flag = -1;
	}
	while (n--)
	{
		*dest_temp = *src_temp;
		dest_temp += flag;
		src_temp += flag;
	}
	return (dest);
}
