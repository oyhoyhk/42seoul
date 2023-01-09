/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 14:21:45 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/02 18:15:55 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cal_len(unsigned int n)
{
	int cnt;

	cnt = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		++cnt;
	}
	return (cnt);
}

char		*ft_itoa(int n)
{
	char			*ret;
	int				cnt;
	unsigned int	temp;

	temp = n < 0 ? -n : n;
	cnt = cal_len(temp) + (n < 0);
	if (!(ret = malloc(sizeof(char) * (cnt + 1))))
		return (NULL);
	if (n < 0)
		ret[0] = '-';
	ret[cnt--] = '\0';
	if (temp == 0)
		ret[cnt] = '0';
	while (temp)
	{
		ret[cnt--] = (temp % 10) + '0';
		temp /= 10;
	}
	return (ret);
}
