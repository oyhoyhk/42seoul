/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:25:26 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/06 17:25:27 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_redirect(t_list *cur)
{
	t_token	*token;

	token = cur->content;
	if (strncmp(token->str, ">", 2)
		&& strncmp(token->str, "<", 2)
		&& strncmp(token->str, "<<", 3)
		&& strncmp(token->str, ">>", 4))
		return (0);

	if (cur->next == NULL)
		return (0);
	token = cur->next->content;
	return (token->type == STRING);
}

static int	is_valid_pipe(t_list *cur)
{
	t_token	*token;

	token = cur->content;
	if (ft_strncmp(token->str, "|", 2)
		|| cur->next == NULL)
		return (0);
	token = cur->next->content;
	return (token->type == STRING || token->type == REDIRECT);
}

int	validate_token(t_list **tokens)
{
	t_list	*cur;
	t_token	*token;


	if (tokens == NULL)
		return (0);
	cur = *tokens;
	if (cur && ((t_token *)cur->content)->type == PIPE)
	{
		ft_lstclear(tokens, token_destory);
		return (1);
	}
	while (cur)
	{
		token = (t_token *)cur->content;
		if ((token->type == REDIRECT && !is_valid_redirect(cur))
			|| (token->type == PIPE && !is_valid_pipe(cur)))
		{
			ft_lstclear(tokens, token_destory);
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}
