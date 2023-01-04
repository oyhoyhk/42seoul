/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:49:36 by yooh              #+#    #+#             */
/*   Updated: 2023/01/04 14:41:52 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_meet_quote(char *input, t_parse_info *info)
{
	if (input[info->i] == '\'' && !info->single && !info->doub)
		info->single = TRUE;
	else if (input[info->i] == '\'' && info->single && !info->doub)
		info->single = FALSE;
	if (input[info->i] == '\"' && !info->single && !info->doub)
		info->doub = TRUE;
	else if (input[info->i] == '\"' && !info->single && info->doub)
		info->doub = FALSE;
}

static void	handle_quote(char **cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (cmd[i])
	{
		temp = parse_quote(cmd[i]);
		free(cmd[i]);
		cmd[i] = temp;
		i++;
	}
}

char	**split_cmd(char *input)
{
	t_parse_info	info;

	ft_bzero(&info, sizeof(t_parse_info));
	while (input[info.i])
	{
		handle_meet_quote(input, &info);
		if (input[info.i] == ' ' && !info.single && !info.doub)
		{
			info.temp = ft_substr(input, info.prev, info.i - info.prev);
			ft_lstadd_back(&info.list, ft_lstnew((void *)info.temp));
			while (input[info.i] == ' ')
				info.i++;
			info.prev = info.i;
			info.i--;
		}
		info.i++;
	}
	info.temp = ft_substr(input, info.prev, info.i - info.prev);
	ft_lstadd_back(&info.list, ft_lstnew((void *)info.temp));
	info.cmd_list = parse_list_to_arr2d(info.list);
	ft_lstclear(&info.list, free_string);
	handle_quote(info.cmd_list);
	return (info.cmd_list);
}
