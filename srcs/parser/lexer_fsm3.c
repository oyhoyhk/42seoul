/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fsm3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 06:40:54 by yooh              #+#    #+#             */
/*   Updated: 2023/01/07 06:42:41 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote1_state(__attribute__((unused))t_list **tokens, t_lexer *lexer)
{
	if (lexer->target == '\'')
		lexer->type = STRING;
	else
		ft_lstadd_back(&lexer->token_buffer, create_new_char(lexer->target));
	return (0);
}

int	quote2_state(__attribute__((unused))t_list **tokens, t_lexer *lexer)
{
	if (lexer->target == '"')
		lexer->type = STRING;
	else if (lexer->target == '$')
	{
		lexer->env_prev = QUOTE_2;
		lexer->type = ENV_VAL;
	}
	else
		ft_lstadd_back(&lexer->token_buffer, create_new_char(lexer->target));
	return (0);
}

int	redirect_state(t_list **tokens, t_lexer *lexer)
{
	return (special_state(tokens, lexer,
			lexer->target == '>' || lexer->target == '<', REDIRECT));
}

int	pipe_state(t_list **tokens, t_lexer *lexer)
{
	return (special_state(tokens, lexer,
			lexer->target == '|', PIPE));
}
