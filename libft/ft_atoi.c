/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:58:13 by yooh              #+#    #+#             */
/*   Updated: 2022/11/15 14:14:32 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char ch)
{
	if (ch == ' '
		|| ch == '\t'
		|| ch == '\n'
		|| ch == '\v'
		|| ch == '\f'
		|| ch == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int			is_negative;
	int			i;
	long long	result;

	i = 0;
	is_negative = 0;
	result = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			is_negative = 1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - '0';
		i++;
	}
	if (is_negative == 1)
		result *= -1;
	return ((int)(result));
}
