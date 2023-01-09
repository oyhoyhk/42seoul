/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 19:55:07 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/02 17:43:36 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int i;
	unsigned int cnt;

	if (!dest && !src)
		return (0);
	cnt = 0;
	i = 0;
	while (src[cnt])
		++cnt;
	if (size == 0)
		return (cnt);
	while (src[i] && i < (size - 1))
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (cnt);
}
