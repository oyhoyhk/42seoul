/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:11:12 by yooh              #+#    #+#             */
/*   Updated: 2022/12/28 20:09:16 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(char **list)
{
	int		i;

	i = 0;
	while (list[i])
		i++;
	return (i);
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

static void	handle_redirect_in(int *start, int *i, int *cur_type, char *input)
{
	*cur_type = REDIRECT_IN;
	*start = *i + 1;
	if (input[*i + 1] == '<')
	{
		*cur_type = REDIRECT_HEREDOC;
		*start = *i + 2;
		*i += 1;
	}
}

void	set_start_point(int	*start, int *i, int *cur_type, char *input)
{
	if (input[*i] == ' ')
	{
		*cur_type = CMD;
		*start = *i + 1;
	}
	if (input[*i] == '<')
		handle_redirect_in(start, i, cur_type, input);
	if (input[*i] == '>')
	{
		*cur_type = REDIRECT_TRUNC_OUT;
		*start = *i + 1;
		if (input[*i + 1] == '>')
		{
			*cur_type = REDIRECT_APPEND_OUT;
			*start = *i + 2;
			*i += 1;
		}
	}
}
