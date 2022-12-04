/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:53:23 by yooh              #+#    #+#             */
/*   Updated: 2022/12/04 19:41:23 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	set_trap_info(int i, int j, t_mlx_info *game);
static void	move_trap(int dx, int dy, t_trap_info *trap_info, t_mlx_info *game);

void	set_mlx_info(t_mlx_info *game, char *filename)
{
	game->mlx = mlx_init();
	game->board = parse_deque_to_arr(parse_file_to_deque(filename));
	game->game_info.present_count = 0;
	game->game_info.total_present = 0;
	game->game_info.game_over = 0;
	game->game_info.traps = NULL;
	game->game_info.traps_count = 0;
	game->game_info.move_count = 0;
	game->game_info.player_count = 0;
	game->game_info.goal_count = 0;
	game->size_info = cal_window_size(game->board);
	game->win = mlx_new_window(game->mlx, game->size_info.width * 60,
			game->size_info.height * 60, "so_long");
}

void	set_player_position(t_mlx_info *game)
{
	int		i;
	int		j;

	i = 0;
	while ((game->board)[i])
	{
		j = 0;
		while ((game->board)[i][j] != '\n' && (game->board)[i][j] != '\0')
		{
			if ((game->board)[i][j] == 'P')
			{
				game->game_info.cur_x = i;
				game->game_info.cur_y = j;
				game->game_info.player_count++;
			}
			if ((game->board)[i][j] == 'C')
				game->game_info.total_present += 1;
			if ((game->board)[i][j] == 'T')
				set_trap_info(i, j, game);
			if (game->board[i][j] == 'E')
				game->game_info.goal_count++;
			j++;
		}
		i++;
	}
}

static void	set_trap_info(int i, int j, t_mlx_info *game)
{
	t_trap_info	*trap_info;

	trap_info = (t_trap_info *) malloc(sizeof(t_trap_info));
	if (trap_info == NULL)
		perror_and_exit(ENOMEM);
	trap_info->x = i;
	trap_info->y = j;
	deque_push(&game->game_info.traps, trap_info);
}

void	patrol_trap(t_mlx_info *game)
{
	t_deque		*cur;
	int			dir;

	cur = game->game_info.traps;
	while (cur)
	{
		if (game->game_info.cur_x == ((t_trap_info *)cur->value)->x
			&& game->game_info.cur_y == ((t_trap_info *)cur->value)->y)
			game_over_lose(*game);
		dir = game->game_info.traps_count;
		if (dir == 0)
			move_trap(-1, 0, (t_trap_info *) cur->value, game);
		if (dir == 1)
			move_trap(0, -1, (t_trap_info *) cur->value, game);
		if (dir == 2)
			move_trap(1, 0, (t_trap_info *) cur->value, game);
		if (dir == 3)
			move_trap(0, 1, (t_trap_info *) cur->value, game);
		cur = cur->right;
		if (cur && game->game_info.cur_x == ((t_trap_info *)cur->value)->x
			&& game->game_info.cur_y == ((t_trap_info *)cur->value)->y)
			game_over_lose(*game);
	}
}

static void	move_trap(int dx, int dy, t_trap_info *trap_info, t_mlx_info *game)
{
	const int	x = trap_info->x;
	const int	y = trap_info->y;

	if (game->board[x + dx][y + dy] == '1'
			|| game->board[x + dx][y + dy] == 'C'
			|| game->board[x + dx][y + dy] == 'T')
		return ;
	if (x + dx == game->game_info.cur_x && y + dy == game->game_info.cur_y)
		game_over_lose(*game);
	trap_info->x = x + dx;
	trap_info->y = y + dy;
	game->board[x][y] = '0';
	game->board[x + dx][y + dy] = 'T';
}
