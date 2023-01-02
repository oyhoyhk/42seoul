/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:23:07 by yooh              #+#    #+#             */
/*   Updated: 2023/01/02 21:02:23 by yooh             ###   ########.fr       */
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
	int		count;

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
			ft_lstadd_back(&word_list, ft_lstnew((void *)(ft_substr(input, prev, i - prev))));
			prev = i + 1;
			count = i;
			while (input[count] != ' ' && input[count] != '\0')
				count++;
			result = env_find(global, ft_substr(input, prev, count - prev));
			i++;
		}
		if (input[i] == '\0')
			break ;
	}
	return (NULL);
}
