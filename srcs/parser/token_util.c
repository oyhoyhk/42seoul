/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:25:23 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/07 06:32:05 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destory_buffer(t_list **buffer)
{
	if (buffer == NULL)
		return ;
	ft_lstclear(buffer, free);
	buffer = NULL;
}

t_list	*create_new_char(char c)
{
	char	*one;

	one = malloc(sizeof(char));
	*one = c;
	return (ft_lstnew(one));
}

t_list	*create_new_char_list(const char *str)
{
	int		i;
	t_list	*ret;

	ret = NULL;
	if (str == NULL)
		return (ret);
	i = 0;
	while (str[i])
	{
		ft_lstadd_back(&ret, create_new_char(str[i]));
		++i;
	}
	return (ret);
}

char	*char_list_to_arr(t_list *char_list)
{
	char	*str;
	int		i;
	t_list	*cur;

	cur = char_list;
	str = malloc(sizeof(char) * (ft_lstsize(char_list) + 1));
	i = 0;
	while (cur)
	{
		str[i] = *(char *)cur->content;
		cur = cur->next;
		++i;
	}
	str[i] = '\0';
	return (str);
}
