/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 21:06:36 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/02 17:16:00 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char *start;

	start = str;
	while (*str)
		++str;
	while (start != str)
	{
		if (*str == (char)c)
			return ((char *)str);
		--str;
	}
	if (*str == (char)c)
		return ((char *)str);
	return (0);
}
