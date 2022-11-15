/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:14:19 by yooh              #+#    #+#             */
/*   Updated: 2022/11/14 11:25:34 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t nmeb, size_t size)
{
	void			*result;

	if (!nmeb || !size)
		return (malloc(0));
	if (INT_MAX / nmeb < size)
		return (malloc(SIZE_MAX));
	result = malloc(nmeb * size);
	if (!result)
		return (NULL);
	ft_bzero(result, nmeb * size);
	return (result);
}
