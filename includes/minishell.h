/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:46 by yooh              #+#    #+#             */
/*   Updated: 2023/01/02 15:23:25 by dongglee         ###   ########.fr       */
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

typedef struct s_pair
{
	char	*key;
	char	*value;
}	t_pair;

/**
 * t_list의 각 content 타입은 t_pair이다.
 */
typedef struct s_envl
{
	t_list	*env_list;
}	t_envl;

typedef struct s_global
{
	t_envl		*envl;
	t_fds		fds;
	t_token		*token;	
}	t_global;

// cmd.c
void		execute_cmd(t_global *global, char **cmd, int i, int count);

// redirect.c
int			handle_redirect_stdin(t_token *token, t_fds fds);
void		handle_redirect_stdout(t_token *token,
				int i, int pipe_count, t_fds fds);

// read.c
void		read_from_stdin(char *word, t_fds fds);
void		start_read(t_global *global);

// tokenize.c
t_token		*tokenize_input(char *input);

// utils.c
int			count_pipe(char **list);
void		set_start_point(int	*start, int *i, int *cur_type, char *input);

// pipe.c
void		run_pipelines(t_global *global, char **pipelines, t_fds fds,
				int pipe_count, pid_t *pid_list);
void		kill_zombie_process(int pipe_count, pid_t *pid_list, t_fds fds);

// free.c
void		free_2d_arr(char **arr);
void		free_token(t_token *token);

// parse.c
char		**parse_readline(char *input);

char	*parse_dollar(char *input, t_global *global);

// signal.c
void		setsignal(void);
void		setsignal_ignored(void);

// builtin_1.c
int			builtin_error_exit(const char *msg, int status_code);
int			builtin_echo(t_global *global, char **cmd);
int			builtin_pwd(t_global *global, char **cmd);
int			builtin_exit(t_global *global, char **cmd);
int			builtin_cd(t_global *global, char **cmd);

// builtin_2.c
int			builtin_env(t_global *global, char **cmd);
int			builtin_unset(t_global *global, char **cmd);
int			builtin_export(t_global *global, char **cmd);

// env_pair.c
void		pair_destroy(t_pair *pair);
t_pair		*pair_make_from_str(const char *env);
char		*pair_to_str(const t_pair *pair);
t_pair		*pair_dup(t_pair *pair);

// env_list.c
t_envl		*env_array_to_list(char **envp);
char		**env_list_to_array(t_envl *lst);
void		env_list_delete_one(t_envl *lst, t_list *emt);
char		*env_getenv(t_global *global, char *key);

// env.c
t_list		*env_find(t_global *global, const char *key);
void		env_update_one(t_global *global, t_pair *pair);
void		env_delete_one(t_global *global, const char *key);

// run_builtin.c
int			is_unprintable_builtin(char **cmd);
int			run_unprintable_builtin(t_global *global, char **cmd);
int			is_printable_builtin(char **cmd);
int			run_printable_builtin(t_global *global, char **cmd);

#endif