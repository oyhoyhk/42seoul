/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:07:49 by yooh              #+#    #+#             */
/*   Updated: 2022/12/04 06:51:32 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void			move(int dx, int dy, t_mlx_info *game);
static void			handle_game_over(t_mlx_info *game, t_game_info *game_info);
static t_game_info	check_object_exist(t_mlx_info *game);

int	key_event(int keycode, t_mlx_info *game)
{
	if (game->game_info.game_over)
		exit(1);
	if (!(keycode == KEY_A || keycode == KEY_D || keycode == KEY_ESC
			|| keycode == KEY_S || keycode == KEY_W))
		return (0);
	if (keycode == KEY_ESC)
		exit(1);
	if (keycode == KEY_A)
		move(0, -1, game);
	else if (keycode == KEY_D)
		move(0, 1, game);
	else if (keycode == KEY_S)
		move (1, 0, game);
	else if (keycode == KEY_W)
		move (-1, 0, game);
	patrol_trap(game);
	draw_bg(*game);
	draw_imgs(*game);
	game->game_info.traps_count = (game->game_info.traps_count + 1) % 4;
	handle_game_over(game, &game->game_info);
	ft_printf("move_count : %d\n", game->game_info.move_count);
	return (0);
}

static t_game_info	check_object_exist(t_mlx_info *game)
{
	int			i;
	int			j;
	int			count;
	t_game_info	result;

	i = 0;
	count = 0;
	result.player_count = 0;
	result.goal_count = 0;
	while (game->board[i])
	{
		j = 0;
		while (game->board[i][j] != '\n' && game->board[i][j] != '\0')
		{
			if (game->board[i][j] == 'P')
				result.player_count = 1;
			if (game->board[i][j] == 'E')
				result.goal_count = 1;
			j++;
		}
		i++;
	}
	return (result);
}

static void	move(int dx, int dy, t_mlx_info *game)
{
	const int		x = game->game_info.cur_x;
	const int		y = game->game_info.cur_y;

	if ((game->board)[x + dx][y + dy] == '1')
		return ;
	game->game_info.move_count += 1;
	mlx_clear_window(game->mlx, game->win);
	if (game->board[x][y] != 'T')
		(game->board)[x][y] = '0';
	if (game->board[x + dx][y + dy] == 'C')
		game->game_info.present_count += 1;
	(game->board)[x + dx][y + dy] = 'P';
	game->game_info.cur_x = x + dx;
	game->game_info.cur_y = y + dy;
}

static void	handle_game_over(t_mlx_info *game, t_game_info *game_info)
{
	t_game_info	result;

	result = check_object_exist(game);
	if (result.goal_count == 0)
	{
		game_info->game_over = 1;
		if (game->game_info.present_count == game->game_info.total_present)
			game_over_win(*game);
		else
			game_over_lose(*game);
	}
	if (result.player_count == 0)
	{
		game_info->game_over = 1;
		game_over_lose(*game);
	}
}
