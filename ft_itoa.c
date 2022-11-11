/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:47:16 by yooh              #+#    #+#             */
/*   Updated: 2022/11/10 16:40:41 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	count_digit_numbers(long long n)
{
	int	count;

	count = 0;
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

void	put_number_in_result(char *result, long long num, int count)
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

char	*get_zero_string(void)
{
	char	*result;

	result = (char *) malloc(sizeof(char) * 2);
	if (!result)
		return (NULL);
	result[0] = '0';
	result[1] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	int			sign;
	int			count;
	char		*result;
	long long	num;

	sign = 0;
	num = (long long) n;
	if (num == 0)
		return (get_zero_string());
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
