/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:11:12 by yooh              #+#    #+#             */
/*   Updated: 2022/12/28 10:22:34 by yooh             ###   ########.fr       */
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

void	show_token(t_token *token)
{
	int		i;
	t_list	*cur;

	i = 0;
	printf("-----------------cmd info------------------\n");
	while (token->cmd_info && token->cmd_info[i])
	{
		printf("[%s]\n", token->cmd_info[i]);
		i++;
	}
	printf("-----------------redirect_in--------------\n");
	cur = token->redirect_in;
	while (cur)
	{
		switch (((t_file_info *)(cur->content))->type){
			case	0 :
				printf("type : CMD\n");
				break;
			case	1 :
				printf("type : REDIRECT_IN\n");
				break;
			case	2 :
				printf("type : REDIRECT_HEREDOC\n");
				break;
			case	3 :
				printf("type : REDIRECT_TRUNC_OUT\n");
				break;
			case	4 :
				printf("type : REDIRECT_APPEND_OUT\n");
				break;
			default	:
				printf("type wrong!!\n");
		}
		printf("[%s]\n", ((t_file_info *)(cur->content))->filename);
		cur = cur->next;
	}
	printf("-----------------redirect_out--------------\n");
	cur = token->redirect_out;
	while (cur)
	{
		switch (((t_file_info *)(cur->content))->type){
			case	0 :
				printf("type : CMD\n");
				break;
			case	1 :
				printf("type : REDIRECT_IN\n");
				break;
			case	2 :
				printf("type : REDIRECT_HEREDOC\n");
				break;
			case	3 :
				printf("type : REDIRECT_TRUNC_OUT\n");
				break;
			case	4 :
				printf("type : REDIRECT_APPEND_OUT\n");
				break;
			default	:
				printf("type wrong!!\n");
		}
		printf("[%s]\n", ((t_file_info *)(cur->content))->filename);
		cur = cur->next;
	}
}