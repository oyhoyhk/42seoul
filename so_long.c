/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 07:03:40 by yooh              #+#    #+#             */
/*   Updated: 2022/12/05 21:06:46 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	extension_check(char *name);
static int	window_close(void);
static int	move_sprites(t_mlx_info *game);

int	main(int argc, char **argv)
{
	t_mlx_info	game;

	if (argc != 2)
		perror_and_exit(EIO);
	extension_check(argv[1]);
	set_mlx_info(&game, argv[1]);
	set_player_position(&game);
	input_valid_check(&game);
	draw_bg(game);
	draw_imgs(game);
	mlx_loop_hook(game.mlx, move_sprites, &game);
	mlx_key_hook(game.win, key_event, &game);
	mlx_hook(game.win, 17, 1L << 15, window_close, NULL);
	mlx_loop(game.mlx);
}

static int	move_sprites(t_mlx_info *game)
{
	static int		count;

	if (!game->game_info.game_over && count == 1500)
	{
		draw_imgs(*game);
		count = 0;
	}
	count++;
	return (0);
}

static int	window_close(void)
{
	exit(0);
	return (0);
}

static void	extension_check(char *name)
{
	ssize_t	length;

	length = ft_strlen(name);
	if (!(name[length - 4] == '.' && name[length - 3] == 'b'\
			&& name[length - 2] == 'e' && name[length - 1] == 'r'))
		perror_and_exit(EIO);
}
