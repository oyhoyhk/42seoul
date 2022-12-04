/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:43:43 by yooh              #+#    #+#             */
/*   Updated: 2022/11/22 08:05:42 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_normal_char(char ch, int *index, int *count)
{
	if (ft_putchar(ch) == -1)
		return (-1);
	*count += 1;
	*index += 1;
	return (1);
}

int	handle_single_flag(char directive, va_list *ap, int *index, int *count)
{
	int	result;

	result = handle_directive(directive, ap);
	if (result == -1)
		return (-1);
	*index += 2;
	*count += result;
	return (1);
}

int	handle_directive(char directive, va_list *ap)
{
	if (directive == 'c')
		return (print_char(va_arg(*ap, int)));
	if (directive == 's')
		return (print_string(va_arg(*ap, char *)));
	if (directive == 'p')
		return (print_pointer(va_arg(*ap, void *)));
	if (directive == 'i' || directive == 'd')
		return (ft_putnbr(va_arg(*ap, int), 1));
	if (directive == 'u')
		return (ft_putnbr(((unsigned int) va_arg(*ap, int)), 1));
	if (directive == 'x')
		return (ft_put_hex(va_arg(*ap, unsigned int), 1, "0123456789abcdef"));
	if (directive == 'X')
		return (ft_put_hex(va_arg(*ap, unsigned int), 1, "0123456789ABCDEF"));
	if (directive == '%')
	{
		ft_putchar('%');
		return (1);
	}
	return (-1);
}
