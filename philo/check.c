/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:51:00 by yooh              #+#    #+#             */
/*   Updated: 2023/01/12 06:36:52 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_ph_death(t_ph *ph)
{
	pthread_mutex_lock(ph->check_mutex);
	*(ph->over_flag) = 1;
	print_dead_msg(ph);
	pthread_mutex_unlock(ph->check_mutex);
	return (DEAD);
}

int	check_over(t_ph *ph)
{
	pthread_mutex_lock(ph->check_mutex);
	if (*(ph->over_flag) == 0)
	{
		pthread_mutex_unlock(ph->check_mutex);
		return (ALIVE);
	}
	else
	{
		pthread_mutex_unlock(ph->check_mutex);
		return (DEAD);
	}
}

int	death_check(t_time last_eat, int die)
{
	t_time	now;
	int		result;

	gettimeofday(&now, NULL);
	result = now.tv_sec * 1000 - last_eat.tv_sec * 1000 + now.tv_usec / 1000
		- last_eat.tv_usec / 1000;
	if (result >= die)
		return (DEAD);
	else
		return (ALIVE);
}
