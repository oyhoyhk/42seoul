/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:23:07 by yooh              #+#    #+#             */
/*   Updated: 2023/01/03 15:14:42 by yooh             ###   ########.fr       */
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

static void	handle_meet_quote(t_parse_info *info, char *input)
{
	if (input[info->i] == '\'' && info->single != 0)
		info->single = 0;
	else if (input[info->i] == '\'' && info->single == 0)
		info->single = info->i;
	if (input[info->i] == '\"' && info->doub != 0)
		info->doub = 0;
	else if (input[info->i] == '\"' && info->doub == 0)
		info->doub = info->i;
}

static int	handle_meet_dollar(t_parse_info *info,
				char *input, t_global *global)
{
	char	*temp;

	temp = ft_substr(input, info->prev, info->i - info->prev);
	ft_lstadd_back(&info->list, ft_lstnew((void *)temp));
	info->prev = info->i + 1;
	info->i++;
	if (input[info->i] == '?')
	{
		ft_lstadd_back(&info->list,
			ft_lstnew((void *) ft_itoa(global->status)));
		info->prev = info->i + 1;
		info->i++;
		return (0);
	}
	while (input[info->i] != '\'' && input[info->i] != '\"'
		&& input[info->i] != ' ' && input[info->i] != '$'
		&& input[info->i] != '\0')
		info->i++;
	info->temp = ft_substr(input, info->prev, info->i - info->prev);
	temp = env_getenv(global, info->temp);
	ft_lstadd_back(&info->list, ft_lstnew((void *)temp));
	free(info->temp);
	info->prev = info->i;
	info->i--;
	return (1);
}

char	*handle_dollar(char *input, t_global *global)
{
	t_parse_info	info;

	ft_bzero(&info, sizeof(t_parse_info));
	while (input[info.i])
	{
		handle_meet_quote(&info, input);
		if (input[info.i] == '$'
			&& (info.single == 0 || (info.doub != 0 && info.single > info.doub))
			&& !handle_meet_dollar(&info, input, global))
			continue ;
		info.i++;
	}
	ft_lstadd_back(&info.list,
		ft_lstnew((void *)ft_substr(input, info.prev, info.i - info.prev)));
	info.result = join_list(info.list);
	ft_lstclear(&info.list, free_string);
	return (info.result);
}
