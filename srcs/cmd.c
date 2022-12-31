/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:09:24 by yooh              #+#    #+#             */
/*   Updated: 2022/12/31 16:33:46 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_absolute_route(char *str)
{
	char		*env;
	char		**list;
	int			i;
	char		*temp;
	char		*result;

	i = 0;
	if (access(str, X_OK) == 0)
	{
		list = ft_split(str, ' ');
		execve(list[0], list, NULL);
	}
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

void	execute_cmd(char **cmd, int i, int count)
{
	char	*absolute_route;

	i = 0;
	count = 0;
	absolute_route = create_absolute_route(cmd[0]);
	if (absolute_route == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(1);
	}
	free(cmd[0]);
	cmd[0] = absolute_route;
	execve(cmd[0], cmd, NULL);
}
