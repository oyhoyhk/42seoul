/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 07:31:41 by yooh              #+#    #+#             */
/*   Updated: 2022/12/05 20:41:48 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_character(int i, int j,
				t_count_info *count_info, t_mlx_info game);
static void	print_score_status(t_mlx_info game);
static void	*get_player_sprites(t_mlx_info game, int count);
static void	*get_present_sprites(t_mlx_info game, int count);

void	draw_imgs(t_mlx_info game)
{
	int					i;
	int					j;
	static t_count_info	count_info;

	i = 0;
	print_score_status(game);
	while ((game.board)[i])
	{
		j = 0;
		while ((game.board)[i][j] != '\n' && (game.board)[i][j] != '\0')
		{
			handle_character(i, j, &count_info, game);
			j++;
		}
		i++;
	}
	count_info.player++;
	count_info.player %= 4;
	count_info.present++;
	count_info.present %= 2;
}

static void	print_score_status(t_mlx_info game)
{
	int		color;
	char	*move_count;
	char	*cur_present_count;

	move_count = ft_itoa(game.game_info.move_count);
	cur_present_count = ft_itoa(game.game_info.total_present
			- game.game_info.present_count);
	color = 0x00FFFFFF;
	mlx_string_put(game.mlx, game.win, 15, 15, color, "SO LONG");
	mlx_string_put(game.mlx, game.win,
		((game.size_info.width - 3) * 60 / 2), 15, color, "MOVE COUNT : ");
	mlx_string_put(game.mlx, game.win,
		((game.size_info.width - 3) * 60 / 2) + 150, 15, color, move_count);
	mlx_string_put(game.mlx, game.win,
		(game.size_info.width * 45), 15, color, "LEFT PRESENTS : ");
	mlx_string_put(game.mlx, game.win,
		(game.size_info.width * 45) + 150, 15, color, cur_present_count);
	free(move_count);
	free(cur_present_count);
}

static void	handle_character(int i, int j,
				t_count_info *count_info, t_mlx_info game)
{
	if ((game.board)[i][j] == '1')
		mlx_put_image_to_window(game.mlx, game.win,
			game.images.wall, j * 60, (i + 1) * 60);
	if ((game.board)[i][j] == 'P')
		mlx_put_image_to_window(game.mlx, game.win,
			get_player_sprites(game, count_info->player), j * 60, (i + 1) * 60);
	if ((game.board)[i][j] == 'E')
		mlx_put_image_to_window(game.mlx, game.win,
			game.images.goal, j * 60, (i + 1) * 60);
	if ((game.board)[i][j] == 'C')
		mlx_put_image_to_window(game.mlx, game.win,
			get_present_sprites(game, count_info->present),
			j * 60, (i + 1) * 60);
	if ((game.board)[i][j] == 'T')
		mlx_put_image_to_window(game.mlx, game.win,
			game.images.trap, j * 60, (i + 1) * 60);
}

static void	*get_present_sprites(t_mlx_info game, int count)
{
	if (count == 1)
		return (game.images.present_1);
	else
		return (game.images.present_2);
}

static void	*get_player_sprites(t_mlx_info game, int count)
{
	if (count % 4 == 0)
		return (game.images.player_1);
	if (count % 4 == 1 || count % 4 == 3)
		return (game.images.player_2);
	if (count % 4 == 2)
		return (game.images.player_3);
	return (NULL);
}
