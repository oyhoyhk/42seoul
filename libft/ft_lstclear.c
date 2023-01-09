/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leedonggyu <leedonggyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 11:45:24 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/06 15:15:03 by leedonggyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *cur;
	t_list *temp;

	if (!lst)
		return ;
	cur = *lst;
	while (cur)
	{
		temp = cur->next;
		del(cur->content);
		free(cur);
		cur = temp;
	}
	*lst = NULL;
}
