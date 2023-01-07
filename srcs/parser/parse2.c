/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 06:35:03 by yooh              #+#    #+#             */
/*   Updated: 2023/01/07 06:35:17 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*make_parse_form(t_list *tokens)
{
	t_list	*cur;
	t_list	*ret;
	t_token	*token;

	ret = NULL;
	cur = tokens;
	while (cur)
	{
		token = cur->content;
		if (token->type == STRING)
			add_string_token(&ret, cur);
		else if (token->type == REDIRECT)
		{
			add_redirect_token(&ret, cur);
			cur = cur->next;
		}
		else if (token->type == PIPE)
			add_process_token(&ret, cur);
		cur = cur->next;
	}
	return (ret);
}

void	file_info_destory(void *ptr)
{
	t_file_info	*file_info;

	file_info = (t_file_info *)ptr;
	free(file_info->filename);
	file_info->filename = NULL;
	free(ptr);
}

void	process_destory(void *ptr)
{
	t_process	*process;

	process = (t_process *)ptr;
	ft_lstclear(&process->redirect_in, file_info_destory);
	ft_lstclear(&process->redirect_out, file_info_destory);
	ft_lstclear(&process->cmd_info, free);
	free(ptr);
}

t_list	*parse(t_global *global, const char *line)
{
	t_list	*tokens;
	t_list	*processes;

	tokens = NULL;
	if (lex(global, line, &tokens)
		|| validate_token(&tokens))
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		return (NULL);
	}
	processes = NULL;
	processes = make_parse_form(tokens);
	ft_lstclear(&tokens, token_destory);
	return (processes);
}
