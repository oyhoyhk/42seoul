/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leedonggyu <leedonggyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 09:13:09 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/01 09:13:19 by leedonggyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		len;
	char	*ret;

	len = 0;
	while (src[len])
		++len;
	ret = malloc(sizeof(char) * (len + 1));
	if (ret == 0)
		return (ret);
	len = 0;
	while (src[len])
	{
		ret[len] = src[len];
		++len;
	}
	ret[len] = '\0';
	return (ret);
}
