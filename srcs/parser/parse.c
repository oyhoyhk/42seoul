/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 06:37:43 by yooh              #+#    #+#             */
/*   Updated: 2023/01/07 06:38:12 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_process(t_list **processes)
{
	t_process	*process;

	process = malloc(sizeof(t_process));
	process->redirect_in = NULL;
	process->redirect_out = NULL;
	process->cmd_info = NULL;
	ft_lstadd_back(processes, ft_lstnew(process));
}

void	add_string_token(t_list **processes, t_list *cur)
{
	t_list		*last_process;
	t_process	*process;
	t_token		*token;

	if (*processes == NULL)
		add_process(processes);
	last_process = ft_lstlast(*processes);
	process = (t_process *)last_process->content;
	token = cur->content;
	ft_lstadd_back(&process->cmd_info, ft_lstnew(strdup(token->str)));
}

int	get_type_redirect(const char *str)
{
	if (ft_strncmp(str, "<", 2) == 0)
		return (REDIRECT_IN);
	if (ft_strncmp(str, ">", 2) == 0)
		return (REDIRECT_TRUNC_OUT);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (REDIRECT_HEREDOC);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (REDIRECT_APPEND_OUT);
	return (-1);
}

void	add_redirect_token(t_list **processes, t_list *cur)
{
	t_list		*last_process;
	t_process	*process;
	t_token		*token;
	t_file_info	*temp;

	if (*processes == NULL)
		add_process(processes);
	last_process = ft_lstlast(*processes);
	process = (t_process *)last_process->content;
	token = cur->content;
	temp = malloc(sizeof(t_file_info));
	temp->type = get_type_redirect(token->str);
	token = cur->next->content;
	temp->filename = ft_strdup(token->str);
	if (temp->type == REDIRECT_IN || temp->type == REDIRECT_HEREDOC)
		ft_lstadd_back(&process->redirect_in, ft_lstnew(temp));
	else if (temp->type == REDIRECT_TRUNC_OUT
		|| temp->type == REDIRECT_APPEND_OUT)
		ft_lstadd_back(&process->redirect_out, ft_lstnew(temp));
}

void	add_process_token(t_list **processes, t_list *cur)
{
	(void) cur;
	if (*processes == NULL)
		add_process(processes);
	add_process(processes);
}
