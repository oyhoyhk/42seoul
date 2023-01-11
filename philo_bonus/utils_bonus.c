/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:52:00 by yooh              #+#    #+#             */
/*   Updated: 2023/01/12 07:52:08 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	is_valid_number(char *str)
{
	int		i;

	i = 0;
	if (ft_strlen(str) > 10)
		return (0);
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int		result;
	int		i;

	if (!is_valid_number(str))
		return (-1);
	result = 0;
	i = 0;
	while (str[i])
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (result == 0)
		return (-1);
	return (result);
}
