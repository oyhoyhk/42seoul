/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 18:26:41 by dongglee          #+#    #+#             */
/*   Updated: 2022/12/31 11:32:38 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pair_destroy(t_pair *pair)
{
	free(pair->key);
	free(pair->value);
	free(pair);
}

/**
 * @brief 등호로 연결된 문자열을 받아서 pair로 바꿔준다.
 * @param char* ex) "key=value"
 * @return t_pair
 */
t_pair	*pair_make_from_str(const char *env)
{
	char	**pair;
	t_pair	*ret;

	ret = malloc(sizeof(t_pair));
	pair = ft_split(env, '=');
	free(pair);
	ret->key = pair[0];
	ret->value = pair[1];
	return (ret);
}

/**
 * @brief t_pair를 등호로 연결된 문자열로 바꿔준다.
 * @param t_pair
 * @return char* ex) "key=value"
 */
char	*pair_to_str(const t_pair *pair)
{
	char	*ret;
	char	*temp;

	temp = ft_strjoin(pair->key, "=");
	ret = ft_strjoin(temp, pair->value);
	free(temp);
	return (ret);
}

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
		ret[i] = pair_to_str(pair);
		++i;
		cur = cur->next;
	}
	ret[i] = NULL;
	return (ret);
}
