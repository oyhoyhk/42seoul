/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:46 by yooh              #+#    #+#             */
/*   Updated: 2022/12/28 14:49:36 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
# include <termios.h>
#include "../libft/libft.h"
#include "gnl.h"

# define TRUE	1
# define FALSE	0

typedef struct s_fds
{
	int stdin_fd;
	int stdout_fd;
	int fd[2];
}	t_fds;

typedef int bool;

enum Property
{
	CMD,
	REDIRECT_IN,
	REDIRECT_HEREDOC,
	REDIRECT_TRUNC_OUT,
	REDIRECT_APPEND_OUT,
};

typedef struct s_tokenizing_info
{
	int		i;
	int		start;
	int		cur_type;
	char	*temp;
	char	*cmd;
}	t_tokenizing_info;

typedef struct s_file_info
{
	int		type;
	char	*filename;
}	t_file_info;

typedef struct s_token
{
	t_list	*redirect_in;
	t_list	*redirect_out;
	char	**cmd_info;
}	t_token;

char	**get_cmd_info(char *str);
void	free_2d_arr(char **arr);
char	*create_absolute_route(char *str);
t_token	*tokenize_input(char *input);
void	read_from_stdin(int fd[2], pid_t pid, char *word, int argc);

void	show_token(t_token *token);

// signal.c
void	setsignal(void);

# endif