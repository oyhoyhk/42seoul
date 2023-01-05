/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:46 by yooh              #+#    #+#             */
/*   Updated: 2023/01/05 21:40:48 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include "libft.h"

typedef enum e_type
{
	NORMAL,
	STRING,
	QUOTE_1,
	QUOTE_2,
	REDIRECT,
	PIPE,
	ENV_VAL
}	t_type;

typedef struct s_token
{
	t_type	type;
	char	*str;
}	t_token;

typedef struct s_lexer
{
	t_type	env_prev;
	t_list	*token_buffer;
	t_list	*env_buffer;
	t_type	type;
	char	target;
}	t_lexer;



// parse.c
t_list	*parse(const char *line);
void	token_destory(void *ptr);


// filter.c
t_list	*filter(t_list *tokens);

// lexer.c
t_list	*lex(const char *line);

// lexer_fsm.c
int	normal_state(t_list **tokens, t_lexer *lexer);
int	string_state(t_list **tokens, t_lexer *lexer);
int	quote1_state(t_list **tokens, t_lexer *lexer);
int	quote2_state(t_list **tokens, t_lexer *lexer);
int	redirect_state(t_list **tokens, t_lexer *lexer);
int	pipe_state(t_list **tokens, t_lexer *lexer);
int	env_state(t_list **tokens, t_lexer *lexer);

// token_util.c
void	destory_buffer(t_list **buffer);
t_list	*create_new_char(char c);
t_list	*create_new_token(t_list *str_lst, t_type type);
t_list	*ft_lstappend(t_list	*lst1, t_list *lst2);
void	token_destory(void *ptr);

int	lexer_branch(t_list **tokens, t_lexer *lexer, char c);

#endif
