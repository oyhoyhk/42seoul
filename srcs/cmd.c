/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:09:24 by yooh              #+#    #+#             */
/*   Updated: 2022/12/30 09:54:00 by yooh             ###   ########.fr       */
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
		ft_putstr_fd((char *)error_str, STDERR_FILENO);
		ft_putstr_fd(result[0], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
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
