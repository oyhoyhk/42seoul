/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 07:47:02 by yooh              #+#    #+#             */
/*   Updated: 2022/12/13 07:00:25 by yooh             ###   ########.fr       */
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

static	void	trim_elements(char **arr)
{
	int		i;
	char	*temp;

	i = 0;
	while (arr[i])
	{
		temp = ft_strtrim(arr[i], " ");
		free(arr[i]);
		arr[i] = temp;
		i++;
	}
}

char	**get_cmd_info(char *cmd, char **env)
{
	char	**path_list;
	char	*temp;
	char	**result;

	path_list = create_path_list(env);
	temp = get_cmd(cmd, path_list);
	if (ft_strchr(cmd, '\''))
	{
		result = ft_split(temp, '\'');
		trim_elements(result);
	}
	else
		result = ft_split(temp, ' ');
	if (result == NULL)
	{
		perror("command not found: ");
		exit(1);
	}
	free_2d_arr((void **)path_list);
	return (result);
}
