/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 08:21:05 by yooh              #+#    #+#             */
/*   Updated: 2022/11/15 14:18:10 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			cnt++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (cnt);
}

static	char	*allocate_word(char *word, char const *s,
		size_t k, size_t word_len)
{
	size_t	i;

	i = 0;
	while (word_len > 0)
		word[i++] = s[k - word_len--];
	word[i] = '\0';
	return (word);
}

static	int	check_index_and_free_result(char **result, size_t cur)
{
	size_t	i;

	if (result[cur])
		return (1);
	i = 0;
	while (i < cur)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}

static	int	create_result(char **result, char const *s,
		char c, size_t word_count)
{
	size_t	i;
	size_t	j;
	size_t	word_len;

	i = 0;
	j = 0;
	word_len = 0;
	while (s[j] && i < word_count)
	{
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && s[j] != c)
		{
			j++;
			word_len++;
		}
		result[i] = (char *) malloc(sizeof(char) * (word_len + 1));
		if (!check_index_and_free_result(result, i))
			return (0);
		allocate_word(result[i], s, j, word_len);
		word_len = '\0';
		i++;
	}
	result[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	char	**result;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **) malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	if (!create_result(result, s, c, word_count))
		return (NULL);
	return (result);
}
