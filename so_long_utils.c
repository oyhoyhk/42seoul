/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:58:08 by yooh              #+#    #+#             */
/*   Updated: 2022/12/04 05:58:32 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_size_info	cal_window_size(char **board)
{
	size_t		m;
	size_t		n;
	t_size_info	result;

	m = 0;
	while (board[m])
		m++;
	n = ft_strlen(board[0]) - 1;
	result.height = m + 1;
	result.width = n;
	return (result);
}

char	*get_present_url(int *present)
{
	if (*present == 0)
		return ("img/present.xpm");
	if (*present == 3)
		*present = 1;
	if (*present == 1)
		return ("img/present_1.xpm");
	if (*present == 2)
		return ("img/present_2.xpm");
	return (NULL);
}

char	*get_player_url(int *player)
{	
	*player %= 4;
	if (*player == 0)
		return ("img/player_1.xpm");
	if (*player % 4 == 1 || *player % 4 == 3)
		return ("img/player_2.xpm");
	if (*player % 4 == 2)
		return ("img/player_3.xpm");
	if (*player % 4 == 3)
		return ("img/player_2.xpm");
	if (*player % 4 == 0)
		return ("img/player_1.xpm");
	return (NULL);
}

void	perror_and_exit(int err)
{
	if (err == EIO)
		ft_printf("map info wrong\n");
	else if (err == ENOMEM)
		ft_printf("malloc failed\n");
	else if (err == EBADF)
		ft_printf("bad file descriptor\n");
	exit(1);
}
