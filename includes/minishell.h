/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:46 by yooh              #+#    #+#             */
/*   Updated: 2022/12/26 11:58:33 by yooh             ###   ########.fr       */
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
#include "libft.h"

# define TRUE	1
# define FALSE	0

typedef struct s_fds
{
	int stdin_fd;
	int stdout_fd;
	int fd[2];
}	t_fds;

typedef int bool;

typedef struct s_token
{
	bool	redirect_in;
	bool	redirect_out_trunc;
	bool	redirect_out_append;
	bool	heredoc;
	char	*infile;
	char	*outfile;
	char	**cmd_info;
}	t_token;

char	**get_cmd_info(char *str);
void	free_2d_arr(char **arr);
char	*create_absolute_route(char *str);
# endif