/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leedonggyu <leedonggyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 11:00:18 by leedonggyu        #+#    #+#             */
/*   Updated: 2020/07/03 11:02:44 by leedonggyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list *bf;
	t_list *cur;

	bf = lst;
	cur = lst;
	while (cur)
	{
		bf = cur;
		cur = cur->next;
	}
	return (bf);
}
