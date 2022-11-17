/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:33:38 by yooh              #+#    #+#             */
/*   Updated: 2022/11/18 08:46:40 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	const size_t	length = ft_strlen(s);
	size_t			i;
	char			*result;

	if (!s || !f)
		return (NULL);
	i = 0;
	result = (char *) malloc(sizeof(char) * length + 1);
	if (!result)
		return (NULL);
	while (i < length)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
