/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:36:32 by yooh              #+#    #+#             */
/*   Updated: 2022/12/04 20:51:19 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	*create_int_arr(int n)
{
	int	*result;
	int	i;

	result = (int *) malloc(sizeof(int) * n);
	if (result == NULL)
		perror_and_exit(ENOMEM);
	i = 0;
	while (i < n)
	{
		result[i] = 0;
		i++;
	}
	return (result);
}

static int	**create_visited_map(char **board)
{
	int		m;
	int		n;
	int		i;
	int		**visited;

	m = 0;
	while (board[m])
		m++;
	n = ft_strlen(board[0]) - 1;
	visited = (int **) malloc(sizeof(int *) * m);
	if (visited == NULL)
		perror_and_exit(ENOMEM);
	i = 0;
	while (i < m)
	{
		visited[i] = create_int_arr(n);
		i++;
	}
	return (visited);
}

static int	dfs_find_goal(int x, int y, t_mlx_info *mlx, int **visited)
{
	int			m;
	int			n;

	m = 0;
	while (mlx->board[m])
		m++;
	n = ft_strlen(mlx->board[0]) - 1;
	if (x == -1 || x == m || y == -1 || y == n
		|| visited[x][y] || mlx->board[x][y] == '1')
		return (0);
	visited[x][y] = 1;
	if (mlx->board[x][y] == 'E')
		return (1);
	return (dfs_find_goal(x - 1, y, mlx, visited)
		|| dfs_find_goal(x + 1, y, mlx, visited)
		|| dfs_find_goal(x, y - 1, mlx, visited)
		|| dfs_find_goal(x, y + 1, mlx, visited));
}

static int	dfs_find_present(int x, int y, t_mlx_info *mlx, int **visited)
{
	int			m;
	int			n;

	m = 0;
	while (mlx->board[m])
		m++;
	n = ft_strlen(mlx->board[0]) - 1;
	if (x == -1 || x == m || y == -1 || y == n
		|| visited[x][y] || mlx->board[x][y] == '1'
		|| mlx->board[x][y] == 'E')
		return (0);
	visited[x][y] = 1;
	if (mlx->board[x][y] == 'C')
		return (1);
	return (dfs_find_present(x - 1, y, mlx, visited)
		+ dfs_find_present(x + 1, y, mlx, visited)
		+ dfs_find_present(x, y - 1, mlx, visited)
		+ dfs_find_present(x, y + 1, mlx, visited));
}

void	escape_check(t_mlx_info *game)
{
	int	**visited_to_find_goal;
	int	**visited_to_find_present;

	visited_to_find_goal = create_visited_map(game->board);
	visited_to_find_present = create_visited_map(game->board);

	if (!dfs_find_goal(game->game_info.cur_x, game->game_info.cur_y,
			game, visited_to_find_goal)
		|| dfs_find_present(game->game_info.cur_x, game->game_info.cur_y,
			game, visited_to_find_present) != game->game_info.total_present)
		perror_and_exit(EIO);
}
