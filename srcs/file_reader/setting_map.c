/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:58:29 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/17 06:09:17 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_map_size(t_global *global, t_list *lst)
{
	t_list	*cur;
	char	*temp;
	int		len;

	cur = lst;
	while (cur)
	{
		temp = (char *)cur->content;
		if (temp[0] == '\n')
			break ;
		global->map_size.height++;
		len = ft_strlen(temp) - 1;
		if (len > global->map_size.width)
			global->map_size.width = len;
		cur = cur->next;
	}
}

t_list	*skip_empty_line(t_list *cur)
{
	char	*temp;

	temp = (char *)cur->content;
	while (cur && temp[0] == '\n')
	{
		cur = cur->next;
		if (cur == NULL)
			break ;
		temp = (char *)cur->content;
	}
	return (cur);
}

int	set_map(t_global *global, t_list *lst)
{
	t_list	*cur;
	int		i;

	cur = skip_empty_line(lst);
	if (cur == NULL)
		return (1);
	set_map_size(global, cur);
	global->map_ptr = malloc(sizeof(char *) * (global->map_size.height + 1));
	global->map_ptr[global->map_size.height] = NULL;
	i = -1;
	while (++i < global->map_size.height)
		global->map_ptr[i] = malloc(sizeof(char) * global->map_size.width);
	if (set_map_emt(global, cur))
	{
		free_2d(global->map_ptr);
		return (1);
	}
	return (0);
}
