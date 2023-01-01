/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:14:41 by yooh              #+#    #+#             */
/*   Updated: 2023/01/01 10:26:57 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*parse_readline_to_list(char *input);
static char		**parse_list_to_arr2d(t_list *list);
static void		set_double_quote_flag(char *input, int i, int *flag);

char	**parse_readline(char *input)
{
	t_list	*list;
	char	**result;

	list = parse_readline_to_list(input);
	result = parse_list_to_arr2d(list);
	return (result);
}

static t_list	*parse_readline_to_list(char *input)
{
	int		i;
	int		start;
	int		in_double_quote;
	t_list	*list;

	i = 0;
	list = NULL;
	in_double_quote = FALSE;
	start = 0;
	while (input[i])
	{
		set_double_quote_flag(input, i, &in_double_quote);
		if (input[i] == '|' && in_double_quote == FALSE)
		{
			ft_lstadd_back(&list,
				ft_lstnew((void *)(ft_substr(input, start, i - start))));
			start = i + 1;
		}
		i++;
	}
	ft_lstadd_back(&list,
		ft_lstnew((void *)(ft_substr(input, start, i - start))));
	return (list);
}

static char	**parse_list_to_arr2d(t_list *list)
{
	const int	length = ft_lstsize(list);
	char		**result;
	int			i;

	result = (char **) malloc(sizeof(char *) * (length + 1));
	i = 0;
	while (i < length)
	{
		result[i] = (char *)(list->content);
		list = list->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

static void	set_double_quote_flag(char *input, int i, int *flag)
{
	if (input[i] == '"' && *flag == TRUE)
		*flag = FALSE;
	else if (input[i] == '"' && *flag == FALSE)
		*flag = TRUE;
}
