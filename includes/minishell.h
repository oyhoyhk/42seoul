/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:46 by yooh              #+#    #+#             */
/*   Updated: 2023/01/06 17:25:52 by dongglee         ###   ########.fr       */
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

enum e_property
{
	REDIRECT_IN,
	REDIRECT_HEREDOC,
	REDIRECT_TRUNC_OUT,
	REDIRECT_APPEND_OUT,
};

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

typedef struct s_file_info
{
	int		type;
	char	*filename;
}	t_file_info;


typedef struct s_process
{
	t_list	*redirect_in;
	t_list	*redirect_out;
	t_list	*cmd_info;
}	t_process;

// parse.c
t_list	*parse(const char *line);
void	process_destory(void *ptr);


// validator.c
int		validate_token(t_list **tokens);

// lexer.c
int		lexer_branch(t_list **tokens, t_lexer *lexer, char c);
int		lex(const char *line, t_list **tokens);

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

#endif
