/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 06:59:08 by yooh              #+#    #+#             */
/*   Updated: 2023/01/08 10:08:12 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 1 3 5 ... 먼저
// 2 4 6 ... 나중에

// 각 쓰레드가 갖고 있어야할 데이터
// 자기 번호, 시작 시간, 
// 뮤텍스는 포크 개수 만큼 있어야 함함

int	cal_time(struct timeval start)
{
	int				result;
	struct timeval	now;

	gettimeofday(&now, NULL);
	result = (now.tv_sec - start.tv_sec) * 1000000
		+ (now.tv_usec - start.tv_usec);
	return (result / 1000);
}

int	is_dead(struct timeval last, int die)
{
	struct timeval	now;
	int				result;

	gettimeofday(&now, NULL);
	result = ((now.tv_sec - last.tv_sec) * 1000000
			+ (now.tv_usec - last.tv_usec)) / 1000;
	if (result > die)
		return (1);
	else
		return (0);
}

void	*test(void *arg)
{
	t_ph			*ph;
	int				cur;
	static int		is_over;

	ph = (t_ph *) arg;
	if (ph->id % 2 == 1)
		usleep(1000);
	gettimeofday(&ph->last_eat, NULL);
	while (1)
	{
		if (is_over)
			break ;
		if (is_dead(ph->last_eat, ph->die))
		{
			is_over = 1;
			printf("%d %d died\n", cur, ph->id + 1);
			break ;
		}
		pthread_mutex_lock(&ph->mutex[ph->left]);
		//왼손에 쥐고
		printf("%d %d has taken a fork\n", cur, ph->id + 1);
		if (is_over)
			break ;
		if (is_dead(ph->last_eat, ph->die))
		{
			is_over = 1;
			printf("%d %d died\n", cur, ph->id + 1);
			pthread_mutex_unlock(&ph->mutex[ph->left]);
			break ;
		}
		ph->fork[ph->left] = 1;
		cur = cal_time(ph->start);
		//오른손에 쥐고
		pthread_mutex_lock(&ph->mutex[ph->right]);
		if (is_over)
			break ;
		if (is_dead(ph->last_eat, ph->die))
		{
			is_over = 1;
			printf("%d %d died\n", cur, ph->id + 1);
			pthread_mutex_unlock(&ph->mutex[ph->left]);
			pthread_mutex_unlock(&ph->mutex[ph->right]);
			break ;
		}
		ph->fork[ph->right] = 1;
		cur = cal_time(ph->start);
		printf("%d %d has taken a fork\n", cur, ph->id + 1);
		//먹기 시작
		cur = cal_time(ph->start);
		printf("%d %d is eating\n", cur, ph->id + 1);
		usleep(ph->eat * 1000);
		if (is_over)
			break ;
		if (is_dead(ph->last_eat, ph->die))
		{
			is_over = 1;
			printf("%d %d died\n", cur + ph->eat, ph->id + 1);
			pthread_mutex_unlock(&ph->mutex[ph->left]);
			pthread_mutex_unlock(&ph->mutex[ph->right]);
			break ;
		}
		gettimeofday(&ph->last_eat, NULL);
		ph->fork[ph->left] = 0;
		ph->fork[ph->right] = 0;
		pthread_mutex_unlock(&ph->mutex[ph->left]);
		pthread_mutex_unlock(&ph->mutex[ph->right]);
		cur = cal_time(ph->start);
		//잠자기 시작
		printf("%d %d is sleeping\n", cur, ph->id + 1);
		usleep(ph->sleep * 1000);
		cur = cal_time(ph->start);
		if (is_over)
			break ;
		if (is_dead(ph->last_eat, ph->die))
		{
			is_over = 1;
			printf("%d %d died\n", cur + ph->sleep, ph->id + 1);
			break ;
		}
		//생각하기 시작
		printf("%d %d is thinking\n", cur, ph->id + 1);
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

int	create_philos(t_info *info)
{
	int				i;
	t_ph			*ph;
	int				*fork;
	struct timeval	time;
	pthread_mutex_t	*mutex;

	i = 0;
	ph = (t_ph *) malloc(sizeof(t_ph) * info->philos_numbers);
	fork = create_forks(info->philos_numbers);
	mutex = create_mutexs(info->philos_numbers);
	if (ph == NULL || fork == NULL || mutex == NULL)
		return (0);
	gettimeofday(&time, NULL);
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
		i++;
	}
	i = 0;
	while (i < info->philos_numbers)
	{
		if (pthread_create(&info->philos[i], NULL, test, (void *)(&ph[i])) < 0)
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