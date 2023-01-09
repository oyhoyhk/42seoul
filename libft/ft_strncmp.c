/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lee <lee@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 22:25:15 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/10/17 15:51:41 by lee              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int pos;

	pos = 0;
	while (s1[pos] && s2[pos] && n > 0)
	{
		if ((unsigned char)s1[pos] != (unsigned char)s2[pos])
			break ;
		++pos;
		--n;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)s1[pos] - (unsigned char)s2[pos]);
}
