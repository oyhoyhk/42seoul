/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fsm2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 06:38:53 by yooh              #+#    #+#             */
/*   Updated: 2023/01/07 06:42:36 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	get_type(char c)
{
	if (c == '\'')
		return (QUOTE_1);
	else if (c == '"')
		return (QUOTE_2);
	else if (c == '>' || c == '<')
		return (REDIRECT);
	else if (c == '|')
		return (PIPE);
	else if (c == '$')
		return (ENV_VAL);
	else
		return (STRING);
}

int	is_special_char_in_env(char c)
{
	return (c == '*' || c == '@' || c == '#'
		|| c == '?' || c == '-' || c == '$'
		|| c == '!' || ft_isdigit(c));
}

int	normal_state(__attribute__((unused))t_list **tokens, t_lexer *lexer)
{
	t_type	type;

	type = get_type(lexer->target);
	if (lexer->target == ' ')
		return (0);
	lexer->type = type;
	if (type == ENV_VAL)
	{
		lexer->env_prev = STRING;
		return (0);
	}
	else if (type == QUOTE_1 || type == QUOTE_2)
		return (0);
	else
		ft_lstadd_back(&lexer->token_buffer, create_new_char(lexer->target));
	return (0);
}

int	string_state(t_list **tokens, t_lexer *lexer)
{
	int	type;

	if (lexer->target == ' ')
	{
		ft_lstadd_back(tokens, create_new_token(lexer->token_buffer, STRING));
		destory_buffer(&lexer->token_buffer);
		lexer->type = NORMAL;
		return (0);
	}
	type = get_type(lexer->target);
	lexer->type = type;
	if (type == QUOTE_1 || type == QUOTE_2)
		return (0);
	else if (type == REDIRECT || type == PIPE)
	{
		ft_lstadd_back(tokens, create_new_token(lexer->token_buffer, STRING));
		destory_buffer(&lexer->token_buffer);
		ft_lstadd_back(&lexer->token_buffer, create_new_char(lexer->target));
	}
	else if (type == ENV_VAL)
		lexer->env_prev = STRING;
	else
		ft_lstadd_back(&lexer->token_buffer, create_new_char(lexer->target));
	return (0);
}
