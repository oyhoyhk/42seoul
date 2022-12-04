/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 07:03:40 by yooh              #+#    #+#             */
/*   Updated: 2022/12/04 19:41:35 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	extension_check(char *name);

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
	mlx_key_hook(game.win, key_event, &game);
	mlx_loop(game.mlx);
}

static void	extension_check(char *name)
{
	ssize_t	length;

	length = ft_strlen(name);
	if (!(name[length - 4] == '.' && name[length - 3] == 'b'\
			&& name[length - 2] == 'e' && name[length - 1] == 'r'))
		perror_and_exit(EIO);
}
