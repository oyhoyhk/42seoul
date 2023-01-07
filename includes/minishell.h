/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:46 by yooh              #+#    #+#             */
/*   Updated: 2023/01/07 06:43:17 by yooh             ###   ########.fr       */
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
# include <unistd.h>
# include "libft.h"

# define TRUE	1
# define FALSE	0

# define TM_RED "\033[0;33m"
# define TM_RESET "\033[0m"

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

typedef struct s_envl
{
	t_list	*env_list;
}	t_envl;

typedef struct s_pair
{
	char	*key;
	char	*value;
}	t_pair;

typedef struct s_global
{
	int			stdin_fd;
	int			stdout_fd;
	int			fd[2];
	t_envl		*envl;
	int			status;
	pid_t		last_pid;
	int			flag;
}	t_global;

// parse.c
t_list		*parse(t_global *global, const char *line);
void		process_destory(void *ptr);
void		add_process_token(t_list **processes, t_list *cur);
void		add_redirect_token(t_list **processes, t_list *cur);
int			get_type_redirect(const char *str);
void		add_string_token(t_list **processes, t_list *cur);
void		add_process(t_list **processes);

// validator.c
int			validate_token(t_list **tokens);

// lexer.c
int			lexer_branch(t_global *global,
				t_list **tokens, t_lexer *lexer, char c);
int			lex(t_global *global, const char *line, t_list **tokens);

// lexer_fsm.c
int			normal_state(t_list **tokens, t_lexer *lexer);
int			string_state(t_list **tokens, t_lexer *lexer);
int			quote1_state(t_list **tokens, t_lexer *lexer);
int			quote2_state(t_list **tokens, t_lexer *lexer);
int			redirect_state(t_list **tokens, t_lexer *lexer);
int			pipe_state(t_list **tokens, t_lexer *lexer);
int			env_state(t_global *global, t_list **tokens, t_lexer *lexer);
t_type		get_type(char c);
int			is_special_char_in_env(char c);
int			special_state(t_list **tokens, t_lexer *lexer,
				int status, int type);

// token_util.c
void		destory_buffer(t_list **buffer);
t_list		*create_new_char(char c);
t_list		*create_new_token(t_list *str_lst, t_type type);
t_list		*ft_lstappend(t_list	*lst1, t_list *lst2);
void		token_destory(void *ptr);
t_list		*create_new_char_list(const char *str);
char		*char_list_to_arr(t_list *char_list);

// signal.c
void		setsignal(void);
void		setsignal_ignored(void);

// env.c
t_list		*env_find(t_global *global, const char *key);
void		env_update_one(t_global *global, t_pair *pair);
void		env_delete_one(t_global *global, const char *key);

// env_list.c
t_envl		*env_array_to_list(char **envp);
char		**env_list_to_array(t_envl *lst);
void		env_list_delete_one(t_envl *lst, t_list *emt);
char		*env_getenv(t_global *global, char *key);

// env_pair.c
void		pair_destroy(t_pair *pair);
t_pair		*pair_make_from_str(const char *env);
char		*pair_to_str(const t_pair *pair);
t_pair		*pair_dup(t_pair *pair);

// builtin_1.c
int			builtin_error_exit(const char *msg, int status_code);
int			builtin_echo(t_global *global, char **cmd);
int			builtin_pwd(t_global *global, char **cmd);
int			builtin_exit(t_global *global, char **cmd);
int			builtin_cd(t_global *global, char **cmd);

// builtin_2.c
int			builtin_env(t_global *global, char **cmd);
int			builtin_unset(t_global *global, char **cmd);

// builtin_3.c
int			builtin_export(t_global *global, char **cmd);

// error.c
int			print_syntax_error(void);
void		print_valid_error(const char *cmd, const char *id);

// run_builtin.c
int			is_unprintable_builtin(char **cmd);
int			run_unprintable_builtin(t_global *global, char **cmd);
int			is_printable_builtin(char **cmd);
int			run_printable_builtin(t_global *global, char **cmd);

// parse2.c
char		**parse_list_to_arr2d(t_list *list);

// utils.c
void		print_logo(void);
int			free_2d_arr(char **arr);
int			is_path(const char *path);
void		kill_zombie_process(int pipe_count,
				t_global *global, pid_t *pid_list);
void		read_from_stdin(char *word, t_global *global, int status);
char		*new_file_name(void);

// redirect.c
int			handle_redirect_stdin(t_process *token, t_global *global);
void		handle_redirect_stdout(t_process *token,
				int i, int pipe_count, t_global *global);

// cmd.c
void		execute_cmd(t_global *global, t_list *cmd_list);

// pipe.c
void		handle_pipes(t_global *global, t_list *pipes);

// gnl.c
char		*get_next_line(int fd);

#endif
