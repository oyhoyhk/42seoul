/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:57:23 by yooh              #+#    #+#             */
/*   Updated: 2023/01/10 11:04:06 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*create_forks(int num)
{
	int		*result;
	int		i;

	result = (int *) malloc(sizeof(int) * num);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < num)
	{
		result[i] = 0;
		i++;
	}
	return (result);
}

pthread_mutex_t	*create_mutexs(int num)
{
	pthread_mutex_t	*list;
	int				i;

	i = 0;
	list = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * num);
	if (list == NULL)
		return (NULL);
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&list[i], NULL);
		i++;
	}
	return (list);
}

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
	if (info->philos_numbers == -1 || info->time_to_die == -1
		|| info->time_to_eat == -1 || info->time_to_sleep == -1
		|| info->times_must_eat == -1)
		return (0);
	info->philos = (pthread_t *) malloc(sizeof(pthread_t)
			* info->philos_numbers);
	if (info == NULL)
		return (0);
	if (!create_philos(info))
		return (0);
	return (1);
}
