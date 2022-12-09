/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:13:16 by yooh              #+#    #+#             */
/*   Updated: 2022/12/06 15:22:44 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *string)
{
	const size_t	len = ft_strlen(string);
	char			*result;
	size_t			i;

	result = (char *) malloc(sizeof(char) * len + 1);
	if (!result || !string)
		return (0);
	i = 0;
	while (string[i])
	{
		result[i] = string[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
