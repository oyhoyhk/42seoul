/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 07:47:02 by yooh              #+#    #+#             */
/*   Updated: 2022/12/09 20:41:56 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_2d_arr(void **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**get_cmd_info(char *cmd, char **env)
{
	char	**path_list;
	char	*temp;
	char	**result;

	path_list = create_path_list(env);
	temp = get_cmd(cmd, path_list);
	result = ft_split(temp, ' ');
	if (result == NULL)
		handle_error();
	free_2d_arr((void **)path_list);
	return (result);
}
