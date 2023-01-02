/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:54:58 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/02 15:23:40 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 명령어가 minishell에 영향을 주는 builtin함수인지를 판별하는 함수
 * cd, export(인자있는), unset, exit
 */
int	is_unprintable_builtin(char **cmd)
{
	return (ft_strncmp(cmd[0], "cd", 3) == 0
		|| ft_strncmp(cmd[0], "unset", 6) == 0
		|| ft_strncmp(cmd[0], "exit", 5) == 0
		|| (ft_strncmp(cmd[0], "export", 7) == 0 && cmd[1] != NULL));
}

int	run_unprintable_builtin(t_global *global, char **cmd)
{
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (builtin_cd(global, cmd));
	if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (builtin_unset(global, cmd));
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (builtin_exit(global, cmd) == 0);
	if ((ft_strncmp(cmd[0], "export", 7) && cmd[1] != NULL) == 0)
		return (builtin_export(global, cmd));
	return (1);
}

/**
 * 명령어가 minishell에 영향 없는 builtin함수인지를 판별하는 함수
 * echo, pwd, export(인자없는), env
 */
int	is_printable_builtin(char **cmd)
{
	return (ft_strncmp(cmd[0], "echo", 5) == 0
		|| ft_strncmp(cmd[0], "pwd", 4) == 0
		|| (ft_strncmp(cmd[0], "export", 7) == 0 && cmd[1] == NULL)
		|| ft_strncmp(cmd[0], "env", 4) == 0);
}

int	run_printable_builtin(t_global *global, char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (builtin_echo(global, cmd));
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (builtin_pwd(global, cmd));
	if (ft_strncmp(cmd[0], "export", 7) == 0 && cmd[1] == NULL)
		return (builtin_export(global, cmd));
	if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (builtin_env(global, cmd));
	return (1);
}