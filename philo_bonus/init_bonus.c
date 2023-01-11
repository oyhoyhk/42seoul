/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:51:04 by yooh              #+#    #+#             */
/*   Updated: 2023/01/12 07:51:33 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	set_info(t_info *info, int argc, char **argv)
{
	struct timeval	time;

	memset(info, 0, sizeof(t_info));
	gettimeofday(&time, NULL);
	info->philos_numbers = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->times_must_eat = ft_atoi(argv[5]);
	else
		info->times_must_eat = 2147483647;
	if (info->philos_numbers == -1 || info->time_to_die == -1
		|| info->time_to_eat == -1 || info->time_to_sleep == -1
		|| info->times_must_eat == -1)
		return (0);
	if (info == NULL)
		return (0);
	return (1);
}
