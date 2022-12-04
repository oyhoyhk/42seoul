/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:32:08 by yooh              #+#    #+#             */
/*   Updated: 2022/12/05 07:13:47 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_char(char **result);
static void	check_row_col(char **result);
static void	check_border(char **result);

void	input_valid_check(t_mlx_info *game)
{
	check_row_col(game->board);
	check_border(game->board);
	check_char(game->board);
	escape_check(game);
	if (game->game_info.player_count != 1 || game->game_info.goal_count != 1
		|| game->game_info.total_present == 0)
		perror_and_exit(EIO);
}

static void	check_char(char **result)
{
	int		i;
	int		j;

	i = 0;
	while (result[i])
	{
		j = 0;
		while (result[i][j] != '\n' && result[i][j] != '\0')
		{
			if (!(result[i][j] == '1' || result[i][j] == '0'
					|| result[i][j] == 'C' || result[i][j] == 'T'
					|| result[i][j] == 'P' || result[i][j] == 'E'
					|| result[i][j] == 'O'))
				perror_and_exit(EIO);
			j++;
		}
		i++;
	}
}

static void	check_row_col(char **result)
{
	int		m;
	int		i;
	ssize_t	length;

	m = 0;
	length = ft_strlen(result[0]);
	while (result[m])
		m++;
	if (m < 3 || m > 22 || length < 3 || length > 43)
		perror_and_exit(EIO);
	i = 0;
	while (i < m)
	{
		if ((i != m - 1 && ft_strlen(result[i]) != length)
			|| (i == m - 1 && ft_strlen(result[i]) + 1 != length))
			perror_and_exit(EIO);
		i++;
	}
}

static void	check_border(char **result)
{
	int	m;
	int	n;
	int	i;
	int	j;

	m = 0;
	while (result[m])
		m++;
	n = ft_strlen(result[0]) - 1;
	i = 0;
	j = 0;
	while (j < n)
	{
		if (result[0][j] != '1' || result[m - 1][j] != '1')
			perror_and_exit(EIO);
		j++;
	}
	while (i < m)
	{
		if (result[0][0] != '1' || result[i][j - 1] != '1')
			perror_and_exit(EIO);
		i++;
	}
}
