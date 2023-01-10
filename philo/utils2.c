/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:47:54 by yooh              #+#    #+#             */
/*   Updated: 2023/01/10 10:49:49 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	over_flag_on(t_ph *ph, int *flag)
{
	pthread_mutex_lock(ph->over_check);
	*flag = 1;
	pthread_mutex_unlock(ph->over_check);
}

int	check_over(t_ph *ph, int *flag)
{
	pthread_mutex_lock(ph->over_check);
	if (*flag == 0)
	{
		pthread_mutex_unlock(ph->over_check);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(ph->over_check);
		return (1);
	}
}

int	death_check(t_time last_eat, int die)
{
	t_time		now;

	gettimeofday(&now, NULL);
	if ((now.tv_sec * 1000000 + now.tv_usec)
		> (last_eat.tv_sec * 1000000 + last_eat.tv_usec + die * 1000))
		return (1);
	else
		return (0);
}

int	get_time(t_time start)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (((now.tv_sec - start.tv_sec) * 1000000
			+ now.tv_usec - start.tv_usec) / 1000);
}

void	print_msg(t_ph *ph, e_ACTION action, int *flag)
{
	if (check_over(ph, flag))
		return ;
	pthread_mutex_lock(ph->print_mutex);
	if (action == LEFT_FORK || action == RIGHT_FORK)
		printf("%d %d has taken a fork\n", get_time(ph->start), ph->id + 1);
	else if (action == EAT)
		printf("%d %d is eating\n", get_time(ph->start), ph->id + 1);
	else if (action == SLEEP)
		printf("%d %d is sleeping\n", get_time(ph->start), ph->id + 1);
	else if (action == THINKING)
		printf("%d %d is thinking\n", get_time(ph->start), ph->id + 1);
	else if (action == DIED)
		printf("%d %d died\n", get_time(ph->start), ph->id + 1);
	else
		printf("./philo error\n");
	pthread_mutex_unlock(ph->print_mutex);
}