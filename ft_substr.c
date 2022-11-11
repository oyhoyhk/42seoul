/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:35:55 by yooh              #+#    #+#             */
/*   Updated: 2022/11/11 12:02:00 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*get_empty_string(void)
{
	char	*result;

	result = (char *) malloc(sizeof(char) * 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	count;
	char			*result;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (get_empty_string());
	i = 0;
	count = 0;
	while (s[start + count] && count < len)
		count++;
	result = (char *) malloc(sizeof(char) * (count + 1));
	if (!result)
		return (NULL);
	while (i < count)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
