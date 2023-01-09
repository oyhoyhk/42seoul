/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 21:08:35 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/02 17:07:57 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int val, size_t num)
{
	char	*temp;

	temp = (char *)ptr;
	while (num--)
	{
		*temp = (char)val;
		++temp;
	}
	return (ptr);
}
