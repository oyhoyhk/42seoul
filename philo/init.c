/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:57:23 by yooh              #+#    #+#             */
/*   Updated: 2023/01/11 20:42:09 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_info(t_info *info, int argc, char **argv, int *over_flag)
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
	info->philos = (pthread_t *) malloc(sizeof(pthread_t)
			* info->philos_numbers);
	if (info == NULL)
		return (0);
	if (!init_philosophers(info, over_flag))
		return (0);
	return (1);
}

void	set_philo(t_info *info, t_ph *ph, int num)
{
	t_time	time;

	gettimeofday(&time, NULL);
	ph->left = num;
	ph->right = (num + 1) % info->philos_numbers;
	ph->die = info->time_to_die;
	ph->eat = info->time_to_eat;
	ph->sleep = info->time_to_sleep;
	ph->start = time;
	ph->id = num;
}

t_ph	*create_philos(t_info *info, int *over_flag)
{
	int				i;
	t_ph			*ph;
	t_fork			*forks;

	i = 0;
	ph = (t_ph *) malloc(sizeof(t_ph) * (info->philos_numbers));
	forks = create_fork_mutexes(info->philos_numbers);
	if (ph == NULL || forks == NULL)
		return (NULL);
	pthread_mutex_init(&info->check_mutex, NULL);
	pthread_mutex_init(&info->print_mutex, NULL);
	while (i < info->philos_numbers)
	{
		ph[i].total_eat = info->times_must_eat;
		ph[i].check_mutex = &info->check_mutex;
		ph[i].print_mutex = &info->print_mutex;
		ph[i].forks = forks;
		ph[i].over_flag = over_flag;
		set_philo(info, &ph[i], i);
		i++;
	}
	return (ph);
}

void	free_philos(t_ph *ph)
{
	free(ph[0].forks);
	free(ph);
}

int	init_philosophers(t_info *info, int *over_flag)
{
	t_ph			*ph;
	int				i;

	i = 0;
	ph = create_philos(info, over_flag);
	if (ph == NULL)
		return (0);
	i = 0;
	while (i < info->philos_numbers)
	{
		if (pthread_create(&info->philos[i], NULL,
				routine, (void *)(&ph[i])) < 0)
		{
			perror("thread create error");
			exit(0);
		}
		i++;
	}
	clean_philos(info);
	free_philos(ph);
	return (1);
}
