/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:09:00 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/10 13:27:49 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_kv	*key_value_create(const char *key, const char *value)
{
	t_kv	*ret;

	ret = malloc(sizeof(t_kv));
	ret->key = ft_strdup(key);
	ret->value = ft_strdup(value);
	return (ret);
}

void	key_value_destory(t_kv *pair)
{
	free(pair->key);
	free(pair->value);
	free(pair);
}
