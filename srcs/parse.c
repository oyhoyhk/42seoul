/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:14:41 by yooh              #+#    #+#             */
/*   Updated: 2023/01/03 16:07:45 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*parse_readline_to_list(char *input);
static void		set_double_quote_flag(char *input, int i,
					int *single_flag, int *double_flag);

char	**parse_readline(char *input)
{
	t_list	*list;
	char	**result;

	list = parse_readline_to_list(input);
	result = parse_list_to_arr2d(list);
	ft_lstclear(&list, free_string);
	return (result);
}

static void	set_single_quote_flag(char *input, int i,
				int *single_flag, int *double_flag)
{
	if (*double_flag == FALSE)
	{
		if (input[i] == '\'' && *single_flag == TRUE)
			*single_flag = FALSE;
		else if (input[i] == '\'' && *single_flag == FALSE)
			*single_flag = TRUE;
	}
}

static t_list	*parse_readline_to_list(char *input)
{
	t_parse_info	info;

	ft_bzero(&info, sizeof(t_parse_info));
	while (input[info.i])
	{
		set_single_quote_flag(input, info.i, &info.single, &info.doub);
		set_double_quote_flag(input, info.i, &info.single, &info.doub);
		if (input[info.i] == '|' && info.doub == FALSE)
		{
			info.temp = ft_substr(input, info.prev, info.i - info.prev);
			ft_lstadd_back(&info.list,
				ft_lstnew((void *)info.temp));
			info.prev = info.i + 1;
		}
		info.i++;
	}
	ft_lstadd_back(&info.list,
		ft_lstnew((void *)(ft_substr(input, info.prev, info.i - info.prev))));
	return (info.list);
}

char	**parse_list_to_arr2d(t_list *list)
{
	const int	length = ft_lstsize(list);
	char		**result;
	int			i;

	result = (char **) malloc(sizeof(char *) * (length + 1));
	i = 0;
	while (i < length)
	{
		result[i] = ft_strdup((char *)(list->content));
		list = list->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

static void	set_double_quote_flag(char *input, int i,
				int *single_flag, int *double_flag)
{
	if (*single_flag == FALSE)
	{
		if (input[i] == '\"' && *double_flag == TRUE)
			*double_flag = FALSE;
		else if (input[i] == '\"' && *double_flag == FALSE)
			*double_flag = TRUE;
	}
}
