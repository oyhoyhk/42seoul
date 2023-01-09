/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 09:18:57 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/02 17:33:49 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *ptr, int c)
{
	while (*ptr)
	{
		if (*ptr == (char)c)
			return ((char *)ptr);
		++ptr;
	}
	if (*ptr == (char)c)
		return ((char *)ptr);
	return (0);
}
