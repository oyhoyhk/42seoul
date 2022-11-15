/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:25:26 by yooh              #+#    #+#             */
/*   Updated: 2022/11/14 09:55:31 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_clear_func(t_list *head, void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;
	void	*temp;

	head = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		temp = f(lst->content);
		if (!temp)
			return (ft_clear_func(head, del));
		new = ft_lstnew(temp);
		if (!new)
		{
			del(temp);
			return (ft_clear_func(head, del));
		}
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}

void	*ft_clear_func(t_list *head, void (*del)(void *))
{
	ft_lstclear(&head, del);
	return (NULL);
}
