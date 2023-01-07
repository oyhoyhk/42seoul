/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 06:31:45 by yooh              #+#    #+#             */
/*   Updated: 2023/01/07 06:32:01 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_new_token(t_list *char_list, t_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	token->str = char_list_to_arr(char_list);
	return (ft_lstnew(token));
}

t_list	*ft_lstappend(t_list *lst1, t_list *lst2)
{
	t_list	*last;

	if (lst1 == NULL)
		return (lst2);
	last = ft_lstlast(lst1);
	last->next = lst2;
	return (lst1);
}

void	token_destory(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	free(token->str);
	free(ptr);
}
