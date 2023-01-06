/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:48:11 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/06 21:23:30 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *my_getenv(const char *key)
{
	char	*temp;

	if (ft_strncmp(key, "?", 2) == 0)
		return (ft_strdup("0"));
	temp = getenv(key);
	if (temp == NULL)
		return (NULL);
	return (ft_strdup(temp));
}
