/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:08:51 by yooh              #+#    #+#             */
/*   Updated: 2023/01/03 19:01:16 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_2d_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (1);
}

void	free_string(void *str)
{
	free((char *)str);
}

void	free_file_info(void *file_info)
{
	free(((t_file_info *)file_info)->filename);
	free(file_info);
}

void	free_token(t_token *token)
{
	free_2d_arr(token->cmd_info);
	ft_lstclear(&(token->redirect_in), free_file_info);
	token->redirect_in = NULL;
	ft_lstclear(&(token->redirect_out), free_file_info);
	token->redirect_out = NULL;
	free(token);
}
