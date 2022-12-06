/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:58:08 by yooh              #+#    #+#             */
/*   Updated: 2022/12/05 20:37:22 by yooh             ###   ########.fr       */
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

void	set_images(t_images *images, t_mlx_info *game)
{
	int	dum;

	images->goal = mlx_xpm_file_to_image(game->mlx,
			"img/goal.xpm", &dum, &dum);
	images->player_1 = mlx_xpm_file_to_image(game->mlx,
			"img/player_1.xpm", &dum, &dum);
	images->player_2 = mlx_xpm_file_to_image(game->mlx,
			"img/player_2.xpm", &dum, &dum);
	images->player_3 = mlx_xpm_file_to_image(game->mlx,
			"img/player_3.xpm", &dum, &dum);
	images->trap = mlx_xpm_file_to_image(game->mlx,
			"img/trap.xpm", &dum, &dum);
	images->present_1 = mlx_xpm_file_to_image(game->mlx,
			"img/present_1.xpm", &dum, &dum);
	images->present_2 = mlx_xpm_file_to_image(game->mlx,
			"img/present_2.xpm", &dum, &dum);
	images->wall = mlx_xpm_file_to_image(game->mlx,
			"img/wall.xpm", &dum, &dum);
	if (!(images->goal && images->player_1 && images->player_2
			&& images->player_3 && images->trap && images->present_1
			&& images->present_2))
		perror_and_exit(ENOMEM);
}

void	free_visited(int **visited, char **board)
{
	int		m;
	int		i;

	m = 0;
	while (board[m])
		m++;
	i = 0;
	while (i < m)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}
