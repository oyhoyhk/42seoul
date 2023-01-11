/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:46:26 by yooh              #+#    #+#             */
/*   Updated: 2023/01/12 07:53:35 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <string.h>

# include <stdio.h>

typedef struct timeval	t_time;

typedef struct s_info
{
	int				philos_numbers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				*forks;
	int				over_flag;
}	t_info;

size_t			ft_strlen(char *str);
int				ft_atoi(char *str);
int				set_info(t_info *info, int argc, char **argv);

#endif