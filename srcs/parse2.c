/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:23:07 by yooh              #+#    #+#             */
/*   Updated: 2023/01/02 13:08:47 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	i = 0;
	prev = 0;
	list = NULL;
	in_single_quote = FALSE;
	in_double_quote = FALSE;
	while (input[i])
	{
		if (input[i] == '\'' && in_single_quote)
			in_single_quote = 0;
		else if (input[i] == '\'' && !in_single_quote)
			in_single_quote = i;
		if (input[i] == '\"' && in_double_quote)
			in_double_quote = 0;
		else if (input[i] == '\"' && !in_double_quote)
			in_double_quote = i;
		if (input[i] == '$' && (in_single_quote == 0 || in_single_quote < in_double_quote))
		{

			ft_lstadd_back(&list, ft_lstnew((void *)ft_substr(input, prev, i - prev)));
			prev = i + 1;
			i++;
			if (input[i] == '?')
			{
				ft_lstadd_back(&list, ft_lstnew((void *) ft_itoa(global->status)));
				prev = i + 1;
				i++;
				continue ;	
			}
			while (input[i] != '\'' && input[i] != '\"' && input[i] != ' ' && input[i] != '$' && input[i] != '\0')
				i++;
			temp = ft_substr(input, prev, i - prev);
			ft_lstadd_back(&list, ft_lstnew((void *)(env_getenv(global, temp))));
			free(temp);
			prev = i;
			i--;
		}
		i++;
	}
	ft_lstadd_back(&list, ft_lstnew((void *)ft_substr(input, prev, i - prev)));
	result = join_list(list);
	ft_lstclear(&list, free_string);
	return (result);
}

char	**split_cmd(char *input)
{
	t_list	*list;
	int		prev;
	int		i;
	int		in_double_quote;
	int		in_single_quote;
	char	**result;

	list = NULL;
	prev = 0;
	i = 0;
	in_double_quote = FALSE;
	in_single_quote = FALSE;
	while (input[i])
	{
		if (input[i] == '\"' && in_double_quote == TRUE)
			in_double_quote = FALSE;
		else if (input[i] == '\"' && in_double_quote == FALSE)
			in_double_quote = TRUE;
		if (input[i] == '\'' && in_single_quote == TRUE)
			in_single_quote = FALSE;
		else if (input[i] == '\'' && in_single_quote == FALSE)
			in_single_quote = TRUE;
		if (input[i] == ' ' && in_single_quote == FALSE && in_double_quote == FALSE)
		{
			if ((input[prev] == '\"' && in_single_quote == TRUE) || (input[prev] == '\'' && in_double_quote == TRUE))
			{
				prev++;
				i--;
			}
			ft_lstadd_back(&list, ft_lstnew((void *)ft_substr(input, prev, i - prev)));
			if (input[prev - 1] == '\"' || (input[prev - 1] == '\'' && !in_double_quote))
				i++; 
			while (input[i] == ' ')
				i++;
			prev = i;
			i--;
		}
		i++;
	}
	if ((input[prev] == '\"' && in_single_quote == TRUE) || (input[prev] == '\'' && in_double_quote == TRUE))
	{
		prev++;
		i--;
	}
	ft_lstadd_back(&list, ft_lstnew((void *)ft_substr(input, prev, i - prev)));
	result = parse_list_to_arr2d(list);
	ft_lstclear(&list, free_string);
	return (result);
}