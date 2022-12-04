/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 07:24:21 by yooh              #+#    #+#             */
/*   Updated: 2022/12/03 21:51:12 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		print_integer(int num);
int		print_unsigned_integer(unsigned int num);
int		print_char(char ch);
int		print_string(char *str);
int		print_pointer(void *ptr);
int		print_integer(int num);
int		print_unsgined_integer(unsigned int num);
int		ft_putchar(char ch);
int		ft_put_hex(unsigned long long num, int count, char *map);
int		ft_putnbr(long long num, int count);
int		handle_normal_char(char ch, int *index, int *count);
int		handle_single_flag(char directive, va_list *ap, int *index, int *count);
int		count_flag_length(char *str);
int		count_percent_char(char *str);
int		ft_includes(char ch, char *set);
int		handle_directive(char directive, va_list *ap);

#endif
