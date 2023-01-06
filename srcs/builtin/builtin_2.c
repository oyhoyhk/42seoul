/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:00:07 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/03 12:37:56 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_global *global, char **cmd)
{
	t_envl	*envl;
	t_list	*cur;
	t_pair	*pair;

	if (cmd[1])
		return (builtin_error_exit("env: too many arguments\n", 1));
	envl = global->envl;
	cur = envl->env_list;
	while (cur)
	{
		pair = cur->content;
		if (pair->value)
			printf("%s=%s\n", pair->key, pair->value);
		cur = cur->next;
	}
	return (0);
}
