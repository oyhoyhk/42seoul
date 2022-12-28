/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:46 by yooh              #+#    #+#             */
/*   Updated: 2022/12/28 20:13:34 by yooh             ###   ########.fr       */
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
# include "gnl.h"

# define TRUE	1
# define FALSE	0

typedef struct s_fds
{
	int	stdin_fd;
	int	stdout_fd;
	int	fd[2];
}	t_fds;

enum e_Property
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

// cmd.cz
char		**get_cmd_info(char *str);
char		*create_absolute_route(char *str);
void		execute_cmd(char **cmd, int i, int count, t_fds fds);

// redirect.c
int			handle_redirect_stdin(t_token *token, int pipe_count, t_fds fds);
void		handle_redirect_stdout(t_token *token, t_fds fds);

// read.c
void		read_from_stdin(int fd[2], char *word, int pipe_count, t_fds fds);
void		start_read(t_fds fds);

// tokenize.c
t_token		*tokenize_input(char *input);

// utils.c
int			count_pipe(char **list);
void		show_token(t_token *token);// 나중에 지워야함
void		set_start_point(int	*start, int *i, int *cur_type, char *input);

// pipe.c
void		run_pipelines(char **pipelines, t_fds fds,
				int pipe_count, pid_t *pid_list);
void		kill_zombie_process(int pipe_count, pid_t *pid_list, t_fds fds);

// free.c
void		free_2d_arr(char **arr);
void		free_token(t_token *token);

// signal.c
void		setsignal(void);

#endif