/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:06:08 by dongglee          #+#    #+#             */
/*   Updated: 2020/07/02 16:15:20 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list		*cur;
	int			ret;

	ret = 0;
	cur = lst;
	while (cur)
	{
		++ret;
		cur = cur->next;
	}
	return (ret);
}
