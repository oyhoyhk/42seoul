/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:23:07 by yooh              #+#    #+#             */
/*   Updated: 2023/01/01 13:25:42 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_string(void *str)
{
	free(str);
}

char	*join_list(t_list *list)
{
	char	*temp;
	char	*result;
	t_list	*cur;

	cur = list;
	temp = ft_calloc(1, 1);
	while (cur)
	{
		result = ft_strjoin(temp, (char *)cur->content);
		free(temp);
		temp = result;
		cur = cur->next;
	}
	return (result);
}

char	*handle_dollar(char *input, t_global *global)
{
	int		i;
	int		prev;
	int		in_single_quote;
	int		in_double_quote;
	t_list	*list;
	char	*result;
	char	*temp;

	global = 0;
	i = 0;
	prev = 0;
	list = NULL;
	in_single_quote = FALSE;
	in_double_quote = FALSE;

	while (input[i])
	{
		if (input[i] == '\'' && in_single_quote == TRUE)
			in_single_quote = FALSE;
		else if (input[i] == '\'' && in_single_quote == FALSE)
			in_single_quote = TRUE;
		if (input[i] == '$' && in_single_quote == FALSE)
		{
			ft_lstadd_back(&list, ft_lstnew((void *)ft_substr(input, prev, i - prev)));
			prev = i + 1;
			while (input[i] != ' ' && input[i] != '\0')
				i++;
			temp = ft_substr(input, prev, i - prev);
			//getenv말고 global->envl에서 가져와야함!!!!
			ft_lstadd_back(&list, ft_lstnew((void *)(getenv(temp) != NULL ? ft_strdup(getenv(temp)) : ft_calloc(1, 1))));
			free(temp);
			prev = i;
		}
		i++;
	}

	ft_lstadd_back(&list, ft_lstnew((void *)ft_substr(input, prev, i - prev)));

	result = join_list(list);
	ft_lstclear(&list, free_string);

	return (result); 
}
