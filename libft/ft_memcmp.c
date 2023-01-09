/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leedonggyu <leedonggyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 19:40:50 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/06/30 20:53:00 by leedonggyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *temp1;
	const unsigned char *temp2;

	temp1 = s1;
	temp2 = s2;
	while (n--)
	{
		if (*temp1 != *temp2)
			return ((int)(*temp1 - *temp2));
		++temp1;
		++temp2;
	}
	return (0);
}
