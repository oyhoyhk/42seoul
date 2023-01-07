/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:41:21 by yooh              #+#    #+#             */
/*   Updated: 2023/01/07 06:41:52 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
