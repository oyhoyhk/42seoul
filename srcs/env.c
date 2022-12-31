/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:01:01 by dongglee          #+#    #+#             */
/*   Updated: 2022/12/31 14:01:19 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param global 환경변수 리스트가 들어있는 변수
 * @param key 찾고싶은 환경변수의 key값
 * @return key가 같은 t_pair 만약 찾지 못했다면 NULL을 리턴.
 */
t_list	*env_find(t_global *global, const char *key)
{
	t_list	*cur;
	t_pair	*pair;
	int		len;

	cur = global->envl->env_list;
	len = ft_strlen(key);
	while (cur)
	{
		pair = (t_pair *)cur->content;
		if (ft_strncmp(pair->key, key, len + 1) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

/**
 * 만약 pair의 key값이 리스트에 존재한다면, 값을 바꾸고, 없다면 추가한다.
 * @param global 환경변수 리스트가 들어있는 변수
 * @param pair 넣고 싶은 환경변수 pair 실제로 리스트에 들어가는 pair는 새로 malloc된다.
 */
void	env_update_one(t_global *global, t_pair *pair)
{
	t_list	*tar;

	tar = env_find(global, pair->key);
	if (tar)
	{
		pair_destroy(tar->content);
		tar->content = pair_dup(pair);
	}
	else
	{
		tar = malloc(sizeof(t_list));
		tar->content = pair_dup(pair);
		tar->next = NULL;
		ft_lstadd_back(&global->envl->env_list, tar);
	}
}

/**
 * @param global 환경변수 리스트가 들어있는 변수
 * @param key 삭제하고 싶은 환경변수의 key값
 */
void	env_delete_one(t_global *global, const char *key)
{
	t_list	*tar;

	tar = env_find(global, key);
	if (tar == NULL)
		return ;
	env_list_delete_one(global->envl, tar);
}
