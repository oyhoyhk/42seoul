/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:09:24 by yooh              #+#    #+#             */
/*   Updated: 2023/01/03 12:35:52 by yooh             ###   ########.fr       */
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

char	**skip_empty_line(char **cmd_info)
{
	int		i;
	int		j;
	int		count;
	char	**result;

	i = -1;
	count = 0;
	while (cmd_info[++i])
	{
		if (ft_strlen(cmd_info[i]))
			count++;
	}
	i = -1;
	j = 0;
	result = (char **) malloc(sizeof(char *) * (count + 1));
	while (cmd_info[++i])
	{
		if (ft_strlen(cmd_info[i]))
		{
			result[j] = ft_strdup(cmd_info[i]);
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}

void	execute_cmd(t_global *global, char **cmd)
{
	char	*absolute_route;
	char	**result;

	result = skip_empty_line(cmd);
	if (!ft_strlen(result[0]))
	{
		ft_putstr_fd("minishell: command not found:\n", 2);
		exit(127);
	}
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
