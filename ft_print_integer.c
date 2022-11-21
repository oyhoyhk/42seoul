/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_integer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 09:43:54 by yooh              #+#    #+#             */
/*   Updated: 2022/11/22 07:37:03 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(long long num, int count)
{
	int			result;

	if (num == 0)
		return (ft_putchar('0'));
	if (num < 0)
	{
		if (ft_putchar('-') == -1)
			return (-1);
		num *= -1;
		count += 1;
	}
	if (num / 10 == 0)
	{
		if (ft_putchar(num + '0') == -1)
			return (-1);
		return (count);
	}
	result = ft_putnbr(num / 10, count + 1);
	if (ft_putchar(num % 10 + '0') == -1)
		return (-1);
	return (result);
}
