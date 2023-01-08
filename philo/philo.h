/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 06:59:23 by yooh              #+#    #+#             */
/*   Updated: 2023/01/08 10:04:52 by yooh             ###   ########.fr       */
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

typedef struct s_info
{
	int				philos_numbers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	pthread_t		*philos;
	int				*forks;
	int				my_number;
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
	pthread_mutex_t	*mutex;
	int				*fork;
}	t_ph;

int			ft_atoi(char *str);
size_t		ft_strlen(char *str);

#endif