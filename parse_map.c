/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:37:44 by yooh              #+#    #+#             */
/*   Updated: 2022/12/03 22:20:57 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_deque	*parse_file_to_deque(char *name)
{
	int		fd;
	t_deque	*dq;
	char	*result;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		perror_and_exit(EBADF);
	result = get_next_line(fd);
	if (result == NULL)
		perror_and_exit(ENOMEM);
	while (result)
	{
		deque_push(&dq, result);
		result = get_next_line(fd);
	}
	return (dq);
}

char	**parse_deque_to_arr(t_deque *dq)
{
	char	**result;
	ssize_t	m;
	ssize_t	i;

	m = deque_length(dq);
	result = (char **) malloc(sizeof(char *) * (m + 1));
	if (result == NULL)
		perror_and_exit(ENOMEM);
	i = 0;
	while (i < m)
	{
		result[i] = dq->value;
		i++;
		dq = dq->right;
	}
	result[i] = NULL;
	return (result);
}
