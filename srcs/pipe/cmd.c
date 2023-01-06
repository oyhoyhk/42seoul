/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:51:45 by yooh              #+#    #+#             */
/*   Updated: 2023/01/06 21:14:32 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (access(result, X_OK) == 0 && free_2d_arr(list))
			return (result);
		free(result);
		i++;
	}
	free_2d_arr(list);
	return (NULL);
}

char	*create_valid_exec_route(t_global *global, const char *str)
{
	if (is_path(str))
	{
		if (access(str, X_OK) == 0)
			return (ft_strdup(str));
		return (NULL);
	}
	return (create_absolute_route(global, str));
}

void	execute_cmd(t_global *global, t_list *cmd_list)
{
	char	*absolute_route;
	char	**result;

	result = parse_list_to_arr2d(cmd_list);
	if (is_printable_builtin(result))
		exit(run_printable_builtin(global, result));
	absolute_route = create_valid_exec_route(global, result[0]);
	if (absolute_route == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(result[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	free(result[0]);
	result[0] = absolute_route;
	execve(result[0], result, env_list_to_array(global->envl));
}
