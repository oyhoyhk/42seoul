/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:41:21 by yooh              #+#    #+#             */
/*   Updated: 2023/01/06 20:46:59 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//char	*skip_empty_string(t_list *list)
//{
//	char	*temp;
//	char	*result;
//	t_list	*cur;

//	temp = ft_calloc(1, 1);
//	cur = list;
//	while (cur)
//	{
//		if (ft_strlen((char *)cur->content))
//		{
//			result = ft_strjoin(temp, (char *)cur->content);
//			free(temp);
//			temp = result;
//		}
//		cur = cur->next;
//	}
//	return (result);
//}

char	**parse_list_to_arr2d(t_list *list)
{
	const int	length = ft_lstsize(list);
	char		**result;
	int			i;

	result = (char **) malloc(sizeof(char *) * (length + 1));
	i = 0;
	while (i < length)
	{
		result[i] = ft_strdup((char *)(list->content));
		list = list->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}
