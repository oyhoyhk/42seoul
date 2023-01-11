/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:47:16 by yooh              #+#    #+#             */
/*   Updated: 2022/11/15 14:15:35 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	count_digit_numbers(long long n)
{
	size_t	count;

	count = 0;
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static	char	*create_zero_string(void)
{
	char	*result;

	result = (char *) malloc(sizeof(char) + 1);
	if (!result)
		return (NULL);
	result[0] = '0';
	result[1] = '\0';
	return (result);
}

static	void	put_number_in_result(char *result, long long num, int count)
{
	result[count--] = '\0';
	while (num > 0)
	{
		result[count] = num % 10 + '0';
		num /= 10;
		count--;
	}
	return ;
}

char	*ft_itoa(int n)
{
	int			sign;
	size_t		count;
	char		*result;
	long long	num;

	sign = 0;
	num = (long long) n;
	if (num == 0)
		return (create_zero_string());
	if (num < 0)
	{
		sign = 1;
		num *= -1;
	}
	count = count_digit_numbers(num) + sign;
	result = (char *) malloc(sizeof(char) * count + 1);
	if (!result)
		return (NULL);
	put_number_in_result(result, num, count);
	if (sign)
		result[0] = '-';
	return (result);
}
