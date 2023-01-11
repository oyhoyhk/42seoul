/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 06:59:08 by yooh              #+#    #+#             */
/*   Updated: 2023/01/11 17:34:34 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_while_waiting(t_ph *ph, int target)
{
	int		gap;

	gap = 250;
	while (1)
	{
		pthread_mutex_lock(&ph->forks[target].fork_mutex);
		if (ph->forks[target].state == OFF)
		{
			ph->forks[target].state = ON;
			pthread_mutex_unlock(&ph->forks[target].fork_mutex);
			print_msg(ph, FORK);
			return (ALIVE);
		}
		pthread_mutex_unlock(&ph->forks[target].fork_mutex);
		usleep(gap);
		if (gap > 50)
			gap -= 50;
		if (check_over(ph) == DEAD)
			return (DEAD);
		if (death_check(ph->last_eat, ph->die) == DEAD)
			return (handle_ph_death(ph));
	}
	return (DEAD);
}

int	check_before_eat(t_ph *ph)
{
	int		time;

	if (check_over(ph) == DEAD)
		return (DEAD);
	if (death_check(ph->last_eat, ph->die) == DEAD)
		return (handle_ph_death(ph));
	gettimeofday(&ph->last_eat, NULL);
	print_msg(ph, EAT);
	time = get_time(ph->start);
	usleep(ph->eat * 800);
	while (get_time(ph->start) - time < ph->eat)
		usleep(200);
	put_down_forks(ph);
	if (check_over(ph) == DEAD)
		return (DEAD);
	return (ALIVE);
}

int	check_while_sleep(t_ph *ph)
{
	int		time;

	print_msg(ph, SLEEP);
	if (check_over(ph) == DEAD)
		return (DEAD);
	if (death_check(ph->last_eat, ph->die) == DEAD)
		return (handle_ph_death(ph));
	time = get_time(ph->start);
	while (get_time(ph->start) - time < ph->sleep)
	{
		usleep(400);
		if (check_over(ph) == DEAD)
			return (DEAD);
		if (death_check(ph->last_eat, ph->die) == DEAD)
			return (handle_ph_death(ph));
	}
	if (check_over(ph) == DEAD)
		return (DEAD);
	if (death_check(ph->last_eat, ph->die) == DEAD)
		return (handle_ph_death(ph));
	return (ALIVE);
}

void	*routine(void *arg)
{
	t_ph			*ph;

	ph = (t_ph *) arg;
	if (ph->id % 2 == 1)
		usleep(200);
	gettimeofday(&ph->last_eat, NULL);
	while (1)
	{
		if (check_while_waiting(ph, ph->left) == DEAD)
			break ;
		if (check_while_waiting(ph, ph->right) == DEAD)
			break ;
		if (check_before_eat(ph) == DEAD)
			break ;
		if (check_while_sleep(ph) == DEAD)
			break ;
		if (check_over(ph) == DEAD)
			break ;
		if (check_over(ph) == DEAD)
			break ;
		print_msg(ph, THINKING);
		if (check_over(ph) == DEAD)
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		over_flag;

	over_flag = 0;
	if (!(argc == 5 || argc == 6))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	set_info(&info, argc, argv, &over_flag);
	return (0);
}
