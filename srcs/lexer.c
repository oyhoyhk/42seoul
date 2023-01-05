/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:39:51 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/05 21:43:49 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		lexer_branch(t_list **tokens, t_lexer *lexer, char c)
{
	lexer->target = c;
	if (lexer->type == NORMAL)
		return(normal_state(tokens, lexer));
	else if (lexer->type == STRING)
		return(string_state(tokens, lexer));
	else if (lexer->type == QUOTE_1)
		return(quote1_state(tokens, lexer));
	else if (lexer->type == QUOTE_2)
		return(quote2_state(tokens, lexer));
	else if (lexer->type == REDIRECT)
		return(redirect_state(tokens, lexer));
	else if (lexer->type == PIPE)
		return(pipe_state(tokens, lexer));
	else if (lexer->type == ENV_VAL)
		return(env_state(tokens, lexer));
	return (1);
}

t_list	*destory_lex_context(t_list **tokens, t_lexer *lexer)
{
	ft_lstclear(tokens, token_destory);
	destory_buffer(&lexer->env_buffer);
	destory_buffer(&lexer->token_buffer);
	return (NULL);
}

t_list	*lex(const char *line)
{
	int			cur;
	t_list		*tokens;
	t_lexer		lexer;

	cur = 0;
	tokens = NULL;
	ft_memset(&lexer, 0, sizeof(t_lexer));
	while (line[cur])
	{
		if (lexer_branch(&tokens, &lexer, line[cur]))
			return (destory_lex_context(tokens, &lexer));
		++cur;
	}
	if (lexer.type == QUOTE_1
		|| lexer.type == QUOTE_2
		|| lexer.type == REDIRECT
		|| lexer.type == PIPE)
		return (destory_lex_context(tokens, &lexer));
	if ((lexer.type == STRING || lexer.type == ENV_VAL)
		&& (lexer_branch(&tokens, &lexer, ' ')))
		return (destory_lex_context(tokens, &lexer));
	return (tokens);
}
