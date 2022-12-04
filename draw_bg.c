/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:03:42 by yooh              #+#    #+#             */
/*   Updated: 2022/12/04 06:40:57 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_bg(t_mlx_info game)
{
	const int	color = 0x00292932;
	int			i;
	int			j;

	i = 1;
	while (i < 60 * game.size_info.width)
	{
		j = 0;
		while (j < 60 * game.size_info.height)
		{
			mlx_pixel_put(game.mlx, game.win, i, j, color);
			j++;
		}
		i++;
	}
}

void	game_over_win(t_mlx_info game)
{
	mlx_clear_window(game.mlx, game.win);
	mlx_string_put(game.mlx, game.win, (game.size_info.width - 3) * 30,
		(game.size_info.height) * 30, 0x00FFFFFF, "Congratuation!!!");
}

void	game_over_lose(t_mlx_info game)
{
	mlx_clear_window(game.mlx, game.win);
	mlx_string_put(game.mlx, game.win, (game.size_info.width - 3) * 30,
		(game.size_info.height) * 30, 0x00FFFFFF, "You lose!!!");
}
