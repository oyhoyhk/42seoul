/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leedonggyu <leedonggyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 13:00:10 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/13 20:21:38 by leedonggyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*next_starting(char *str, char c)
{
	while (*str && *str == c)
		++str;
	if (*str == '\0')
		return (0);
	return (str);
}

static int			str_cnt(char *str, char c)
{
	int	ret;

	ret = 0;
	while ((str = next_starting(str, c)))
	{
		++ret;
		while (*str && *str != c)
			++str;
	}
	return (ret);
}

static char			*str_dup(char **str, char c)
{
	int		i;
	int		cnt;
	char	*ret;

	i = 0;
	cnt = 0;
	while ((*str)[i] && (*str)[i] != c)
	{
		++cnt;
		++i;
	}
	if (!(ret = malloc(sizeof(char) * (cnt + 1))))
		return (NULL);
	ret[cnt] = '\0';
	i = 0;
	while (cnt--)
	{
		ret[i] = **str;
		++i;
		++(*str);
	}
	return (ret);
}

static void			*free_all(char **ret, int inx)
{
	int i;

	i = 0;
	while (i < inx)
	{
		free(ret[i]);
		++i;
	}
	free(ret);
	return (NULL);
}

char				**ft_split(char const *s, char c)
{
	char	**ret;
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	if (!(ret = malloc(sizeof(char*) * (str_cnt(str, c) + 1))))
		return (NULL);
	i = 0;
	while ((str = next_starting(str, c)))
	{
		if (!(ret[i] = str_dup(&str, c)))
			return (free_all(ret, i));
		++i;
	}
	ret[i] = NULL;
	return (ret);
}
