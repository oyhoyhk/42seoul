/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 08:35:05 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/02 18:12:08 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	len_of_num(char *str)
{
	int ret;

	ret = 0;
	while ('0' <= *str && *str <= '9')
	{
		++ret;
		++str;
	}
	return (ret);
}

int			ft_atoi(char *str)
{
	unsigned long long int	ret;
	int						sign;

	ret = 0;
	sign = 0;
	while (is_space(*str))
		++str;
	if (*str == '-')
	{
		++str;
		sign = 1;
	}
	else if (*str == '+')
		++str;
	if (len_of_num(str) >= 20)
		return (sign == 0 ? -1 : 0);
	while ('0' <= *str && *str <= '9')
	{
		ret *= 10;
		ret += *str - '0';
		++str;
	}
	if (sign == 1)
		return (-(unsigned int)ret);
	return ((int)ret);
}
