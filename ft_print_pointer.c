/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 09:46:36 by yooh              #+#    #+#             */
/*   Updated: 2022/11/22 07:31:15 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pointer(void *ptr)
{
	if (write(1, "0x", 2) == -1)
		return (-1);
	if (!ptr)
	{
		if (ft_putchar('0') == -1)
			return (-1);
		return (3);
	}
	return (ft_put_hex((unsigned long long) ptr, 1, "0123456789abcdef") + 2);
}
