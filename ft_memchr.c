/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:20:23 by yooh              #+#    #+#             */
/*   Updated: 2022/11/10 11:15:02 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *buf, int c, size_t n)
{
	unsigned char	*temp;

	temp = (unsigned char *)buf;
	while (n > 0)
	{
		if (*temp == (unsigned char)c)
			return ((void *) temp);
		temp++;
		n--;
	}
	return (0);
}
