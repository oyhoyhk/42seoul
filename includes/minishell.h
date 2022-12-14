/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:46 by yooh              #+#    #+#             */
/*   Updated: 2023/01/06 07:40:27 by yooh             ###   ########.fr       */
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
	int		in_single_quote;
	int		in_double_quote;
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

typedef struct s_parse_info
{
	int		i;
	int		prev;
	int		single;
	int		doub;
	t_list	*list;
	char	*result;
	char	*temp;
	char	**cmd_list;
}	t_parse_info;

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
	int			status;
	pid_t		last_pid;
}	t_global;

// cmd.c
void		execute_cmd(t_global *global, char **cmd);

// redirect.c
int			handle_redirect_stdin(t_token *token, t_global *global);
void		handle_redirect_stdout(t_token *token,
				int i, int pipe_count, t_fds fds);

// read.c
void		read_from_stdin(char *word, t_global *global, int status);
void		execute_readline(t_global *global, char *input);

// tokenize.c
t_token		*tokenize_input(char *input);
int			handle_prev_token_and_set(t_tokenizing_info *info,
				t_token *token, char *input);

// utils.c
int			count_pipe(char **list);
void		set_start_point(int	*start, int *i, int *cur_type, char *input);
int			parse_input_into_token(t_tokenizing_info *info,
				char *input, t_token *token);
void		print_logo(void);

char		*new_file_name(void);
int			handle_special_case(char *input, t_global *global);
void		cal_info(int *sing, int *doub, char ch);

// pipe.c
void		run_pipelines(t_global *global, char **pipelines,
				int pipe_count, pid_t *pid_list);
void		kill_zombie_process(int pipe_count,
				t_global *global, pid_t *pid_list);

// free.c
int			free_2d_arr(char **arr);
void		free_token(t_token *token);
void		free_string(void *str);

// parse.c
char		**parse_readline(char *input);
char		**parse_list_to_arr2d(t_list *list);

// parse2.c
char		*handle_dollar(char *input, t_global *global);
char		**split_cmd(char *input);

char		*parse_quote(char *str);

// parse_dollar.c
void		parse_dollars(char **origin, t_global *global);
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

// bu9iltin_3.c
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

// error.c
int			print_syntax_error(void);
void		print_valid_error(const char *cmd, const char *id);

#endif