/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 18:26:41 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/01 16:40:52 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * key와 value가 등호로 연결된 배열을 환경변수 연결 리스트로 변환
 * malloc을 통해 리스트를 생성함
 */
t_envl	*env_array_to_list(char **envp)
{
	t_envl	*ret;
	int		i;

	ret = malloc(sizeof(t_envl));
	i = 0;
	ret->env_list = NULL;
	while (envp[i])
	{
		ft_lstadd_back(&(ret->env_list),
			ft_lstnew(pair_make_from_str(envp[i])));
		++i;
	}
	return (ret);
}

/**
 * key와 value를 등호로 연결하여 문자열 리스트로 반환
 * 리스트의 마지막값은 NULL
 */
char	**env_list_to_array(t_envl *lst)
{
	char	**ret;
	int		i;
	t_list	*cur;
	t_pair	*pair;

	ret = malloc(sizeof(char *) * (ft_lstsize(lst->env_list) + 1));
	i = 0;
	cur = lst->env_list;
	while (cur)
	{
		pair = (t_pair *)cur->content;
		if (pair->value)
			ret[i] = pair_to_str(pair);
		++i;
		cur = cur->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	env_list_delete_one(t_envl *lst, t_list *emt)
{
	t_list	*cur;

	if (emt == NULL)
		return ;
	cur = lst->env_list;
	if (emt == cur)
	{
		lst->env_list = cur->next;
		pair_destroy(emt->content);
		return ;
	}
	while (cur && cur->next)
	{
		if (cur->next == emt)
		{
			cur->next = cur->next->next;
			pair_destroy(emt->content);
			return ;
		}
		cur = cur->next;
	}
}

char	*env_getenv(t_global *global, char *key)
{
	t_list	*tar;
	t_pair	*pair;

	tar = env_find(global, key);
	if (!tar)
		return (ft_calloc(1, 1));
	pair = (t_pair *)tar->content;
	if (!pair->value)
		return (ft_calloc(1, 1));
	return (strdup(pair->value));
}
