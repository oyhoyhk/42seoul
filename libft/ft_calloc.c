/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 09:13:54 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/02 17:34:59 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = malloc(nmemb * size);
	if (!ret)
		return (NULL);
	while (i < nmemb * size)
		ret[i++] = 0;
	return (ret);
}
