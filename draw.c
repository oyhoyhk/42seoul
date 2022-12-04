/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 07:31:41 by yooh              #+#    #+#             */
/*   Updated: 2022/12/03 10:06:31 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_character(int i, int j,
				t_count_info *count_info, t_mlx_info game);
static void	draw_img(int i, int j, t_mlx_info game, char *url);
static void	print_score_status(t_mlx_info game);

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
	count_info.present++;
}

static void	print_score_status(t_mlx_info game)
{
	int		color;

	color = 0x00FFFFFF;
	mlx_string_put(game.mlx, game.win, 15, 15, color, "SO LONG");
	mlx_string_put(game.mlx, game.win,
		((game.size_info.width - 3) * 60 / 2), 15, color, "MOVE COUNT : ");
	mlx_string_put(game.mlx, game.win,
		((game.size_info.width - 3) * 60 / 2) + 150, 15, color,
		ft_itoa(game.game_info.move_count));
	mlx_string_put(game.mlx, game.win,
		(game.size_info.width * 49), 15, color, "LEFT PRESENTS : ");
	mlx_string_put(game.mlx, game.win,
		(game.size_info.width * 49) + 150, 15, color,
		ft_itoa(game.game_info.total_present - game.game_info.present_count));
}

static void	handle_character(int i, int j,
				t_count_info *count_info, t_mlx_info game)
{
	if ((game.board)[i][j] == '1')
		draw_img(i, j, game, "img/wall.xpm");
	if ((game.board)[i][j] == 'P')
		draw_img(i, j, game, get_player_url(&count_info->player));
	if ((game.board)[i][j] == 'E')
		draw_img(i, j, game, "img/goal.xpm");
	if ((game.board)[i][j] == 'C')
		draw_img(i, j, game, get_present_url(&count_info->present));
	if ((game.board)[i][j] == 'T')
		draw_img(i, j, game, "img/trap.xpm");
}

static void	draw_img(int i, int j, t_mlx_info game, char *url)
{
	void	*img;
	int		dum;

	img = mlx_xpm_file_to_image(game.mlx, url, &dum, &dum);
	mlx_put_image_to_window(game.mlx, game.win, img, j * 60, (i + 1) * 60);
}
