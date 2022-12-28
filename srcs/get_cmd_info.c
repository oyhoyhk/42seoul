/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:09:24 by yooh              #+#    #+#             */
/*   Updated: 2022/12/26 10:50:13 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_cmd_info(char *str)
{
	char		**result;
	char		*cmd;
	const char	*error_str = "minishell: command not found: ";

	result = ft_split(str, ' ');
	if (ft_strncmp(result[0], "<", -1) == 0
		|| ft_strncmp(result[0], "<<", -1) == 0
		|| access(result[0], X_OK) == 0)
		return (result);
	cmd = create_absolute_route(result[0]);
	if (cmd == NULL)
	{
		write(2, error_str, ft_strlen(error_str));
		write(2, result[0], ft_strlen(result[0]));
		write(2, "\n", 1);
		free_2d_arr(result);
		exit(1);
	}
	free((void *)result[0]);
	result[0] = cmd;
	return ((char **)result);
}

char	*create_absolute_route(char *str)
{
	char		*env;
	char		**list;
	int			i;
	char		*temp;
	char		*result;

	i = 0;
	env = getenv("PATH");
	list = ft_split(env, ':');
	while (list[i])
	{
		temp = ft_strjoin(list[i], "/");
		result = ft_strjoin(temp, str);
		free(temp);
		if (access(result, X_OK) == 0)
		{
			free_2d_arr(list);
			return (result);
		}
		free(result);
		i++;
	}
	free_2d_arr(list);
	return (NULL);
}