/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 07:20:22 by yooh              #+#    #+#             */
/*   Updated: 2022/11/22 08:04:20 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int			i;
	int			count;
	va_list		*ptr_ap;
	va_list		ap;

	va_start(ap, format);
	ptr_ap = &ap;
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (handle_single_flag(format[i + 1], ptr_ap, &i, &count) == -1)
				return (-1);
		}
		else
			handle_normal_char(format[i], &i, &count);
	}
	va_end(ap);
	return (count);
}
