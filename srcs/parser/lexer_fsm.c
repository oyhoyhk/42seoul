/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fsm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:24:24 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/07 06:50:58 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_state(t_list **tokens, t_lexer *lexer, int status, int type)
{
	lexer->type = get_type(lexer->target);
	if (status)
	{
		ft_lstadd_back(&lexer->token_buffer, create_new_char(lexer->target));
		return (0);
	}
	else
	{
		ft_lstadd_back(tokens, create_new_token(lexer->token_buffer, type));
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

static int	handle_question_mark(t_global *global, t_lexer *lexer)
{
	char	*env_value;

	env_value = ft_itoa(global->status);
	lexer->token_buffer = ft_lstappend(lexer->token_buffer,
			create_new_char_list(env_value));
	free(env_value);
	lexer->type = lexer->env_prev;
	if (lexer->type == NORMAL)
		lexer->type = STRING;
	lexer->env_buffer = NULL;
	return (0);
}

static void	handle_rest_case(t_global *global, t_lexer *lexer)
{
	char	*env_key;
	char	*env_value;

	if (lexer->env_buffer == NULL)
	{
		if (!((lexer->env_prev != QUOTE_2)
				&& (lexer->target == '\''
					|| lexer->target == '\"')))
			ft_lstadd_back(&lexer->token_buffer, create_new_char('$'));
	}
	else
	{
		env_key = char_list_to_arr(lexer->env_buffer);
		env_value = env_getenv(global, env_key);
		if (env_value)
			lexer->token_buffer = ft_lstappend(lexer->token_buffer,
					create_new_char_list(env_value));
		destory_buffer(&lexer->env_buffer);
		free(env_key);
		free(env_value);
	}
}

int	env_state(t_global *global, t_list **tokens, t_lexer *lexer)
{
	if (lexer->env_buffer == NULL && is_special_char_in_env(lexer->target))
	{
		if (lexer->target == '?')
			return (handle_question_mark(global, lexer));
		else
			return (1);
	}
	else if (ft_isalnum(lexer->target) || lexer->target == '_')
	{
		ft_lstadd_back(&lexer->env_buffer, create_new_char(lexer->target));
		return (0);
	}
	else
		handle_rest_case(global, lexer);
	lexer->type = lexer->env_prev;
	return (lexer_branch(global, tokens, lexer, lexer->target));
}
