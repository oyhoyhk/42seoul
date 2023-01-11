/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:47:54 by yooh              #+#    #+#             */
/*   Updated: 2023/01/11 18:46:10 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(t_time start)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (((now.tv_sec - start.tv_sec) * 1000000
			+ now.tv_usec - start.tv_usec) / 1000);
}

void	print_msg(t_ph *ph, int action)
{
	pthread_mutex_lock(ph->print_mutex);
	if (death_check(ph->last_eat, ph->die) == DEAD)
	{
		printf("%d %d died\n", get_time(ph->start), ph->id + 1);
		pthread_mutex_unlock(ph->print_mutex);
		return ;
	}
	if (check_over(ph) == DEAD)
	{
		pthread_mutex_unlock(ph->print_mutex);
		return ;
	}
	if (action == FORK)
		printf("%d %d has taken a fork\n", get_time(ph->start), ph->id + 1);
	else if (action == EAT)
		printf("%d %d is eating\n", get_time(ph->start), ph->id + 1);
	else if (action == SLEEP)
		printf("%d %d is sleeping\n", get_time(ph->start), ph->id + 1);
	else if (action == THINKING)
		printf("%d %d is thinking\n", get_time(ph->start), ph->id + 1);
	else
		printf("./philo error\n");
	pthread_mutex_unlock(ph->print_mutex);
}

t_fork	*create_fork_mutexes(int num)
{
	t_fork	*result;
	int		i;

	result = (t_fork *) malloc(sizeof(t_fork) * (num));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < num)
	{
		result[i].state = 0;
		pthread_mutex_init(&result[i].fork_mutex, NULL);
		i++;
	}
	return (result);
}

void	clean_philos(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->philos_numbers)
	{
		pthread_join(info->philos[i], NULL);
		i++;
	}
}

void	put_down_forks(t_ph *ph)
{
	pthread_mutex_lock(&ph->forks[ph->left].fork_mutex);
	ph->forks[ph->left].state = OFF;
	pthread_mutex_unlock(&ph->forks[ph->left].fork_mutex);
	pthread_mutex_lock(&ph->forks[ph->right].fork_mutex);
	ph->forks[ph->right].state = OFF;
	pthread_mutex_unlock(&ph->forks[ph->right].fork_mutex);
}
