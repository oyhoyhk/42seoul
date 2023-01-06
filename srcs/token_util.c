/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:25:23 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/06 17:25:24 by dongglee         ###   ########.fr       */
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
	char *one;

	one = malloc(sizeof(char));
	*one = c;
	return (ft_lstnew(one));
}

t_list	*create_new_token(t_list *str_lst, t_type type)
{
	char	*str;
	t_token	*token;
	t_list	*cur;
	int		i;

	token = malloc(sizeof(t_token));
	token->type = type;
	cur = str_lst;
	str = malloc(sizeof(char) * (ft_lstsize(str_lst) + 1));
	i = 0;
	while (cur)
	{
		str[i] = *(char *)cur->content;
		cur = cur->next;
		++i;
	}
	str[i] = '\0';
	token->str = str;
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
