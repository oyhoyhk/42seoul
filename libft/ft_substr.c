/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:35:55 by yooh              #+#    #+#             */
/*   Updated: 2022/11/15 14:17:28 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	*get_empty_string(void)
{
	void	*result;

	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	count;
	char	*result;

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
