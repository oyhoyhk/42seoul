/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 06:59:23 by yooh              #+#    #+#             */
/*   Updated: 2023/01/10 11:04:28 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <stdio.h>

# define OFF		0
# define ON			1

typedef enum e_action
{
	LEFT_FORK,
	RIGHT_FORK,
	EAT,
	SLEEP,
	THINKING,
	DIED,
}	e_ACTION;

typedef struct timeval	t_time;

typedef struct s_info
{
	int				philos_numbers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	pthread_t		*philos;
	int				*forks;
	pthread_mutex_t	*mutex;
}	t_info;

typedef struct s_ph
{
	int				id;
	int				left;
	int				right;
	int				die;
	int				eat;
	int				sleep;
	struct timeval	start;
	struct timeval	last_eat;
	struct timeval	last_sleep;
	pthread_mutex_t	*mutex;
	int				*fork;
	pthread_mutex_t	*death_check;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*over_check;
}	t_ph;

int				ft_atoi(char *str);
size_t			ft_strlen(char *str);
void			over_flag_on(t_ph *ph, int *flag);
int				check_over(t_ph *ph, int *flag);
int				death_check(t_time last_eat, int die);
int				get_time(t_time start);
void			print_msg(t_ph *ph, e_ACTION action, int *flag);
pthread_mutex_t	*create_mutexs(int num);
int				*create_forks(int num);
int				set_info(t_info *info, int argc, char **argv);
int				create_philos(t_info *info);

#endif