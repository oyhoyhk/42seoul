/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:07:00 by yooh              #+#    #+#             */
/*   Updated: 2022/12/03 19:38:26 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_H
# define DEQUE_H

# include <stdlib.h>
# include <sys/types.h>

typedef struct s_deque
{
	struct s_deque	*left;
	struct s_deque	*right;
	void			*value;
	ssize_t			index;
}	t_deque;

t_deque	*create_deque(void *value);
t_deque	*deque_push(t_deque **head, void *value);
ssize_t	deque_length(t_deque *head);
void	free_deque(t_deque *dq);

#endif