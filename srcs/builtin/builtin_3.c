/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:58:00 by yooh              #+#    #+#             */
/*   Updated: 2023/01/04 07:21:53 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_add(t_global *global, char **cmd);
static int	export_print(t_global *global);

/**
 * export - null가능, 
 */

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

int	builtin_export(t_global *global, char **cmd)
{
	if (cmd[1] == NULL)
		return (export_print(global));
	else
		return (export_add(global, cmd));
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
