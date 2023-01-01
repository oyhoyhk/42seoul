/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:08:51 by yooh              #+#    #+#             */
/*   Updated: 2023/01/01 13:10:20 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	free_string(void *str)
{
	free((char *)str);
}

void	free_token(t_token *token)
{
	free_2d_arr(token->cmd_info);
	ft_lstclear(&(token->redirect_in), free_string);
	ft_lstclear(&(token->redirect_out), free_string);
	free(token);
}
