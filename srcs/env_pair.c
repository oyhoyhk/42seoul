/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pair.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:55:53 by dongglee          #+#    #+#             */
/*   Updated: 2022/12/31 13:51:16 by dongglee         ###   ########.fr       */
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
 * pair deep copy
 * if pair is NULL then return NULL
 */
t_pair	*pair_dup(t_pair *pair)
{
	t_pair	*ret;

	if (pair == NULL)
		return (NULL);
	ret = malloc(sizeof(t_pair));
	ret->key = ft_strdup(pair->key);
	ret->value = ft_strdup(pair->value);
	return (ret);
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
