/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:23:07 by yooh              #+#    #+#             */
/*   Updated: 2022/12/31 20:20:15 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_dollar(char *input, t_global *global)
{
	int		single_quote;
	int		i;
	int		prev;
	t_list	*word_list;
	t_list	*result;

	single_quote = FALSE;
	word_list = NULL;
	i = 0;
	prev = 0;
	while (input[i])
	{
		if (!single_quote && input[i] == '\'')
			single_quote = TRUE;
		if (single_quote && input[i] == '\'')
			single_quote = FALSE;
		if (single_quote == FALSE && input[i] == '$')
		{
			printf("%s", ft_substr(input, prev, i- prev));
			ft_lstadd_back(&word_list, ft_lstnew((void *)(ft_substr(input, prev, i - prev))));
			prev = i + 1;
			while (input[i] != ' ' && input[i] != '\0')
				i++;
			result = env_find(global, ft_substr(input, prev, i - prev));
			printf("%s", ((t_pair *)result->content)->value);
		}
		if (input[i] == '\0')
			break ;
		i++;
	}
	return (NULL);
}
