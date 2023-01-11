/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 06:59:23 by yooh              #+#    #+#             */
/*   Updated: 2023/01/11 20:39:37 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdio.h>

# define DEAD		0
# define ALIVE		1

# define ON			1
# define OFF		0

# define INTERVAL	50

typedef enum e_action
{
	FORK,
	EAT,
	SLEEP,
	THINKING,
	DIED,
}	t_action;

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
	pthread_mutex_t	check_mutex;
	pthread_mutex_t	print_mutex;
}	t_info;

typedef struct s_fork
{
	int				state;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_ph
{
	int				id;
	int				left;
	int				right;
	int				die;
	int				eat;
	int				sleep;
	int				total_eat;
	struct timeval	start;
	struct timeval	last_eat;
	t_fork			*forks;
	pthread_mutex_t	*check_mutex;
	pthread_mutex_t	*print_mutex;
	int				*over_flag;
}	t_ph;

int				ft_atoi(char *str);
size_t			ft_strlen(char *str);
int				check_over(t_ph *ph);
int				death_check(t_time last_eat, int die);
int				get_time(t_time start);
void			print_msg(t_ph *ph, int action);
int				set_info(t_info *info, int argc, char **argv, int *over_flag);
t_ph			*create_philos(t_info *info, int *over_flag);
void			set_philo(t_info *info, t_ph *ph, int num);
t_fork			*create_fork_mutexes(int num);
int				init_philosophers(t_info *info, int *over_flag);
void			*routine(void *arg);
t_fork			*create_fork_mutexes(int num);
void			clean_philos(t_info *info);
int				handle_ph_death(t_ph *ph);
int				check_over(t_ph *ph);
int				death_check(t_time last_eat, int die);
void			put_down_forks(t_ph *ph);
#endif