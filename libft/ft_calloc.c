/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:14:19 by yooh              #+#    #+#             */
/*   Updated: 2022/11/15 14:20:25 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmeb, size_t size)
{
	void			*result;

	if (!nmeb || !size)
		return (malloc(0));
	result = malloc(nmeb * size);
	if (!result)
		return (NULL);
	ft_bzero(result, nmeb * size);
	return (result);
}
