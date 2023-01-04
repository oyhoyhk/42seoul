/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:04:45 by yooh              #+#    #+#             */
/*   Updated: 2023/01/04 14:44:29 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_meet_single_quote(t_parse_info *info, char *str)
{
	if (str[info->i] == '\'' && info->single && !info->doub)
	{
		info->temp = ft_substr(str, info->prev, info->i - info->prev);
		ft_lstadd_back(&info->list, ft_lstnew((void *) info->temp));
		info->prev = info->i + 1;
		info->single = 0;
	}
	else if (str[info->i] == '\'' && !info->single && !info->doub)
	{
		if (info->prev < info->i)
		{
			info->temp = ft_substr(str, info->prev, info->i - info->prev);
			ft_lstadd_back(&info->list, ft_lstnew((void *) info->temp));
		}
		info->single = 1;
		info->prev = info->i + 1;
	}
}

static void	handle_meet_double_quote(t_parse_info *info, char *str)
{
	if (str[info->i] == '\"' && !info->single && info->doub)
	{
		info->temp = ft_substr(str, info->prev, info->i - info->prev);
		ft_lstadd_back(&info->list, ft_lstnew((void *) info->temp));
		info->prev = info->i + 1;
		info->doub = 0;
	}
	else if (str[info->i] == '\"' && !info->single && !info->doub)
	{
		if (info->prev < info->i)
		{
			info->temp = ft_substr(str, info->prev, info->i - info->prev);
			ft_lstadd_back(&info->list, ft_lstnew((void *) info->temp));
		}
		info->prev = info->i + 1;
		info->doub = 1;
	}
}

static char	*skip_empty_string(t_list *list)
{
	char	*temp;
	char	*result;
	t_list	*cur;

	temp = ft_calloc(1, 1);
	cur = list;
	while (cur)
	{
		if (ft_strlen((char *)cur->content))
		{
			result = ft_strjoin(temp, (char *)cur->content);
			free(temp);
			temp = result;
		}
		cur = cur->next;
	}
	return (result);
}

char	*parse_quote(char *str)
{
	t_parse_info	info;
	char			*result;

	ft_bzero(&info, sizeof(t_parse_info));
	while (str[info.i])
	{
		handle_meet_single_quote(&info, str);
		handle_meet_double_quote(&info, str);
		info.i++;
	}
	info.temp = ft_substr(str, info.prev, info.i - info.prev);
	ft_lstadd_back(&info.list, ft_lstnew((void *) info.temp));
	result = skip_empty_string(info.list);
	ft_lstclear(&info.list, free_string);
	return (result);
}
