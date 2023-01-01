/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:00:07 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/01 16:36:36 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key(const char *key)
{
	int	i;

	if (ft_isdigit(key[0]))
		return (FALSE);
	else
	{
		i = 0;
		while (key[i])
		{
			if (!(ft_isalnum(key[i]) || key[i] == '_'))
				return (FALSE);
			++i;
		}
	}
	return (TRUE);
}

void	print_valid_error(const char *cmd, const char *id)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(id, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

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

int	builtin_unset(t_global *global, char **cmd)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (cmd[i])
	{
		if (is_valid_key(cmd[i]) == FALSE)
		{
			print_valid_error("unset", cmd[i]);
			ret = 1;
		}
		else
			env_delete_one(global, cmd[i]);
		++i;
	}
	return (ret);
}

static int	export_print(t_global *global)
{
	t_pair	*pair;
	t_list	*cur;

	cur = global->envl->env_list;
	while (cur)
	{
		pair = cur->content;
		if (pair->value)
			printf("declare -x %s=\"%s\"\n", pair->key, pair->value);
		else
			printf("declare -x %s\n", pair->key);
		cur = cur->next;
	}
	return (0);
}

static int	export_add(t_global *global, char **cmd)
{
	int		i;
	t_pair	*pair;
	t_list	*cmp;
	int		ret;

	i = 1;
	ret = 0;
	while (cmd[i])
	{
		pair = pair_make_from_str(cmd[i]);
		cmp = env_find(global, pair->key);
		if (!is_valid_key(pair->key))
		{
			print_valid_error("export", cmd[i]);
			ret = 1;
		}
		else if ((!cmp) || (cmp && pair->value))
			env_update_one(global, pair);
		pair_destroy(pair);
		++i;
	}
	return (ret);
}

/**
 * export - null가능, 
 */
int	builtin_export(t_global *global, char **cmd)
{

	if (cmd[1] == NULL)
		return (export_print(global));
	else
		return (export_add(global, cmd));
}
