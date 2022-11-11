/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:13:16 by yooh              #+#    #+#             */
/*   Updated: 2022/11/10 11:13:26 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *string)
{
	const size_t	len = ft_strlen(string);
	char			*result;
	int				i;

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
