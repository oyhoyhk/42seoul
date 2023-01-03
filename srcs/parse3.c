/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:49:36 by yooh              #+#    #+#             */
/*   Updated: 2023/01/03 14:24:05 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_meet_single_quote(t_parse_info *info, char *input)
{
	char	*temp;

	if (info->doub)
		return ;
	if (info->single)
		info->single = 0;
	else
		info->single = info->i;
	temp = ft_substr(input, info->prev, info->i - info->prev);
	if (temp && ft_strlen(temp))
		ft_lstadd_back(&info->list, ft_lstnew((void *)temp));
	info->prev = info->i;
	while (input[info->i] != '\'')
		info->i++;
	temp = ft_substr(input, info->prev, info->i - info->prev);
	if (temp && ft_strlen(temp))
		ft_lstadd_back(&info->list, ft_lstnew((void *)temp));
	info->prev = info->i + 1;
}

static void	handle_meet_double_quote(t_parse_info *info, char *input)
{
	char	*temp;

	if (info->single)
		return ;
	if (info->doub)
		info->doub = 0;
	else
		info->doub = info->i;
	temp = ft_substr(input, info->prev, info->i - info->prev);
	if (temp && ft_strlen(temp))
		ft_lstadd_back(&info->list, ft_lstnew((void *)temp));
	info->prev = ++info->i;
	while (input[info->i] != '\"')
		info->i++;
	temp = ft_substr(input, info->prev, info->i - info->prev);
	if (temp && ft_strlen(temp))
		ft_lstadd_back(&info->list, ft_lstnew((void *)temp));
	info->prev = info->i + 1;
}

static void	handle_meet_space(t_parse_info *info, char *input)
{
	char	*temp;

	temp = ft_substr(input, info->prev, info->i - info->prev);
	ft_lstadd_back(&info->list, ft_lstnew((void *)temp));
	info->prev = info->i + 1;
	while (input[info->i] == ' '
		&& (input[info->i] != '\"' || input[info->i] != '\''))
		info->i++;
	info->prev = info->i;
	info->i -= 1;
}

char	**split_cmd(char *input)
{
	t_parse_info	info;

	ft_bzero(&info, sizeof(t_parse_info));
	while (input[info.i])
	{
		if (input[info.i] == '\'')
			handle_meet_single_quote(&info, input);
		if (input[info.i] == '\"')
			handle_meet_double_quote(&info, input);
		if (input[info.i] == ' ')
			handle_meet_space(&info, input);
		info.i++;
	}
	if (input[info.prev] == '\"' || input[info.prev] == '\'')
	{
		info.prev++;
		info.i--;
	}
	ft_lstadd_back(&info.list,
		ft_lstnew((void *)ft_substr(input, info.prev, info.i - info.prev)));
	info.cmd_list = parse_list_to_arr2d(info.list);
	ft_lstclear(&info.list, free_string);
	return (info.cmd_list);
}
