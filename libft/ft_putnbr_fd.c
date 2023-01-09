/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leedonggyu <leedonggyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 19:06:22 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/03 13:36:41 by leedonggyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			buff[11];
	int				i;
	unsigned int	unsigned_n;

	if (fd < 0)
		return ;
	i = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		unsigned_n = -n;
	}
	else
		unsigned_n = n;
	while (1)
	{
		buff[i++] = unsigned_n % 10 + '0';
		unsigned_n /= 10;
		if (unsigned_n == 0)
			break ;
	}
	while (i > 0)
	{
		write(fd, &buff[--i], 1);
	}
}
