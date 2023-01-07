/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:39:51 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/07 06:51:28 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_branch(t_global *global, t_list **tokens, t_lexer *lexer, char c)
{
	lexer->target = c;
	if (lexer->type == NORMAL)
		return (normal_state(tokens, lexer));
	else if (lexer->type == STRING)
		return (string_state(tokens, lexer));
	else if (lexer->type == QUOTE_1)
		return (quote1_state(tokens, lexer));
	else if (lexer->type == QUOTE_2)
		return (quote2_state(tokens, lexer));
	else if (lexer->type == REDIRECT)
		return (redirect_state(tokens, lexer));
	else if (lexer->type == PIPE)
		return (pipe_state(tokens, lexer));
	else if (lexer->type == ENV_VAL)
		return (env_state(global, tokens, lexer));
	return (1);
}

static int	destory_lex_context(t_list **tokens, t_lexer *lexer)
{
	ft_lstclear(tokens, token_destory);
	destory_buffer(&lexer->env_buffer);
	destory_buffer(&lexer->token_buffer);
	return (1);
}

int	lex(t_global *global, const char *line, t_list **tokens)
{
	int			cur;
	t_lexer		lexer;

	*tokens = NULL;
	cur = 0;
	ft_memset(&lexer, 0, sizeof(t_lexer));
	while (line[cur])
	{
		if (lexer_branch(global, tokens, &lexer, line[cur]))
			return (destory_lex_context(tokens, &lexer));
		++cur;
	}
	if (lexer.type == QUOTE_1
		|| lexer.type == QUOTE_2
		|| lexer.type == REDIRECT
		|| lexer.type == PIPE)
		return (destory_lex_context(tokens, &lexer));
	if ((lexer.type == STRING || lexer.type == ENV_VAL)
		&& (lexer_branch(global, tokens, &lexer, ' ')))
		return (destory_lex_context(tokens, &lexer));
	return (0);
}
