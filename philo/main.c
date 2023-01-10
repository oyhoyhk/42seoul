/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 06:59:08 by yooh              #+#    #+#             */
/*   Updated: 2023/01/10 11:04:40 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	drop_fork(t_ph *ph)
{
	pthread_mutex_lock(&ph->mutex[ph->left]);
	ph->fork[ph->left] = 0;
	pthread_mutex_unlock(&ph->mutex[ph->left]);
	pthread_mutex_lock(&ph->mutex[ph->right]);
	ph->fork[ph->right] = 0;
	pthread_mutex_unlock(&ph->mutex[ph->right]);
	gettimeofday(&ph->last_eat, NULL);
}

int	check_while_do_sleep(t_ph *ph, e_ACTION action, int *flag)
{
	int		target;

	if (check_over(ph, flag))
		return (1);
	if (action == EAT)
		target = ph->eat;
	else
		target = ph->sleep;
	print_msg(ph, action, flag);
	while (!death_check(ph->last_eat, ph->die) && target > 0)
	{
		usleep(50 * 1000);
		target -= 50;
	}
	if (action == EAT)
		drop_fork(ph);
	if (target == 0)
	{
		if (action == SLEEP)
			print_msg(ph, THINKING, flag);
		return (0);
	}
	else
	{
		print_msg(ph, DIED, flag);
		over_flag_on(ph, flag);
		return (1);
	}
}

int	check_while_wating_fork(t_ph *ph, e_ACTION action, int *flag)
{
	int	count;
	int	target;

	count = 250;
	if (action == LEFT_FORK)
		target = ph->left;
	else
		target= ph->right;
	while (1)
	{
		if (check_over(ph, flag))
			return (1);
		if (death_check(ph->last_eat, ph->die))
		{
			print_msg(ph, DIED, flag);
			over_flag_on(ph, flag);
			return (1);
		}
		pthread_mutex_lock(&ph->mutex[target]);
		if (ph->fork[target] == 0)
		{
			ph->fork[target] = 1;
			print_msg(ph, action, flag);
			pthread_mutex_unlock(&ph->mutex[target]);
			return (0);
		}
		pthread_mutex_unlock(&ph->mutex[target]);
		usleep(count);
		if (count > 50)
			count -= 50;
	}
	return (1);
}

void	*routine(void *arg)
{
	t_ph			*ph;
	static int		flag;

	ph = (t_ph *)arg;
	if (ph->id % 2 == 1)
		usleep (500);
	gettimeofday(&ph->last_eat, NULL);
	while (1)
	{
		if (check_while_wating_fork(ph, LEFT_FORK, &flag))
			break ;
		if (check_while_wating_fork(ph, RIGHT_FORK, &flag))
			break ;
		if (check_while_do_sleep(ph, EAT, &flag))
			break ;
		if (check_while_do_sleep(ph, SLEEP, &flag))
			break ;
	}
	return (NULL);
}

void	handle_create_thread_error(int num, t_info *info)
{
	int		i;

	i = 0;
	while (i < num)
	{
		pthread_detach(info->philos[i]);
		i++;
	}
}

int	create_philos(t_info *info)
{
	int				i;
	t_ph			*ph;
	int				*fork;
	struct timeval	time;
	pthread_mutex_t	*mutex;
	pthread_mutex_t *death_check;
	pthread_mutex_t *print_mutex;
	pthread_mutex_t *over_check;

	i = 0;
	ph = (t_ph *) malloc(sizeof(t_ph) * info->philos_numbers);
	fork = create_forks(info->philos_numbers);
	mutex = create_mutexs(info->philos_numbers);
	death_check = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	print_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	over_check = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (ph == NULL || fork == NULL || mutex == NULL || death_check == NULL
		|| print_mutex == NULL || over_check == NULL)
		return (0);
	gettimeofday(&time, NULL);
	pthread_mutex_init(death_check, NULL);
	pthread_mutex_init(print_mutex, NULL);
	pthread_mutex_init(over_check, NULL);
	while (i < info->philos_numbers)
	{
		if (i == 0)
			ph[i].left = info->philos_numbers - 1;
		else
			ph[i].left = i - 1;
		ph[i].right = i;
		ph[i].eat = info->time_to_eat;
		ph[i].die = info->time_to_die;
		ph[i].sleep = info->time_to_sleep;
		ph[i].id = i;
		ph[i].start = time;
		ph[i].fork = fork;
		ph[i].mutex = mutex;
		ph[i].death_check = death_check;
		ph[i].print_mutex = print_mutex;
		ph[i].over_check = over_check;
		i++;
	}
	i = 0;
	while (i < info->philos_numbers)
	{
		if (pthread_create(&info->philos[i], NULL, routine, (void *)(&ph[i])) < 0)
		{
			perror("thread create error");
			exit(0);
		}
		i++;
	}
	i = -1;
	while (++i < info->philos_numbers)
		pthread_join(info->philos[i], NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (!(argc == 5 || argc == 6))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	set_info(&info, argc, argv);
	return (0);
}