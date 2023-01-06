/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fsm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:24:24 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/06 17:25:11 by dongglee         ###   ########.fr       */
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
	lexer->type = get_type(lexer->target);
	if (lexer->target == '>' || lexer->target == '<')
		ft_lstadd_back(&lexer->token_buffer, create_new_char(lexer->target));
	else
	{
		ft_lstadd_back(tokens, create_new_token(lexer->token_buffer, REDIRECT));
		destory_buffer(&lexer->token_buffer);
	}
	if (lexer->target == ' ')
		lexer->type = NORMAL;
	if (lexer->type == ENV_VAL)
		lexer->env_prev = STRING;

	return (0);
}

int	pipe_state(t_list **tokens, t_lexer *lexer)
{

	lexer->type = get_type(lexer->target);
	if (lexer->target == '|')
		ft_lstadd_back(&lexer->token_buffer, create_new_char(lexer->target));
	else
	{
		ft_lstadd_back(tokens, create_new_token(lexer->token_buffer, PIPE));
		destory_buffer(&lexer->token_buffer);
	}
	if (lexer->target == ' ')
		lexer->type = NORMAL;
	else if (lexer->type == ENV_VAL)
		lexer->env_prev = STRING;
	else
		ft_lstadd_back(&lexer->token_buffer, create_new_char(lexer->target));
	return (0);
}

int	env_state(t_list **tokens, t_lexer *lexer)
{

	if (lexer->env_buffer == NULL && is_special_char_in_env(lexer->target))
	{
		if (lexer->target == '?')
		{
			ft_lstadd_back(&lexer->token_buffer, create_new_char('0'));
			lexer->type = lexer->env_prev;
			if (lexer->type == NORMAL)
				lexer->type = STRING;
			lexer->env_buffer = NULL;
			return (0);
		}
		else
			return(1);
	}
	else if (ft_isalnum(lexer->target) || lexer->target == '_')
	{
		ft_lstadd_back(&lexer->env_buffer, create_new_char(lexer->target));
		return (0);
	}
	else
	{
		if (lexer->env_buffer == NULL)
		{
			if (!((lexer->env_prev != QUOTE_2)
				&& (lexer->target == '\''
					|| lexer->target == '\"')))
			ft_lstadd_back(&lexer->token_buffer, create_new_char('$'));
		}
		else
		{
			ft_lstadd_front(&lexer->env_buffer, create_new_char('['));
			ft_lstadd_back(&lexer->env_buffer, create_new_char(']'));
			lexer->token_buffer = ft_lstappend(lexer->token_buffer, lexer->env_buffer);
			lexer->env_buffer = NULL;
		}
	}
	lexer->type = lexer->env_prev;
	return (lexer_branch(tokens, lexer, lexer->target));
}
