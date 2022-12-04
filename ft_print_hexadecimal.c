/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexadecimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 09:47:01 by yooh              #+#    #+#             */
/*   Updated: 2022/11/22 07:48:23 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_hex(unsigned long long num, int count, char *map)
{
	int			result;

	if (num / 16 == 0)
	{
		if (ft_putchar(map[num]) == -1)
			return (-1);
		return (count);
	}
	result = ft_put_hex(num / 16, count + 1, map);
	if (result == -1)
		return (-1);
	if (ft_putchar(map[num % 16]) == -1)
		return (-1);
	return (result);
}
