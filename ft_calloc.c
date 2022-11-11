/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:14:19 by yooh              #+#    #+#             */
/*   Updated: 2022/11/11 14:37:32 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmeb, size_t size)
{
	void	*result;

	if ((size_t) -1 / nmeb < size)
		return (NULL);
	if (!nmeb || !size)
		return (NULL);
	result = malloc(nmeb * size);
	if (!result)
		return (NULL);
	ft_bzero(result, nmeb * size);
	return (result);
}
