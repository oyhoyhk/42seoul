/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:09:24 by yooh              #+#    #+#             */
/*   Updated: 2023/01/02 16:03:56 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_path(const char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			return (TRUE);
		++i;
	}
	return (FALSE);
}

char	*create_absolute_route(t_global *global, const char *str)
{
	t_list		*lst;
	char		**list;
	int			i;
	char		*temp;
	char		*result;

	i = 0;
	lst = env_find(global, "PATH");
	if (lst == NULL || lst->content == NULL)
		return (NULL);
	list = ft_split(((t_pair *)lst->content)->value, ':');
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

char	*create_valid_exec_route(t_global *global, const char *str)
{
	if (is_path(str))
		return (ft_strdup(str));
	return (create_absolute_route(global, str));
}

void	execute_cmd(t_global *global, char **cmd, int i, int count)
{
	char	*absolute_route;

	i = 0;
	count = 0;
	if (is_printable_builtin(cmd))
		exit(run_printable_builtin(global, cmd));
	absolute_route = create_valid_exec_route(global, cmd[0]);
	if (absolute_route == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(1);
	}
	free(cmd[0]);
	cmd[0] = absolute_route;
	execve(cmd[0], cmd, env_list_to_array(global->envl));
}
