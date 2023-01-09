/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 06:19:08 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/02 17:32:44 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	void *ret;

	if (!src && !dest)
		return (NULL);
	ret = dest;
	while (num--)
	{
		*(char *)dest = *(char *)src;
		++dest;
		++src;
	}
	return (ret);
}
