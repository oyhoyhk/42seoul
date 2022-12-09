/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:14:19 by yooh              #+#    #+#             */
/*   Updated: 2022/12/07 07:55:00 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
