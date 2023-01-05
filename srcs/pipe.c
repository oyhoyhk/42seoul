/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:30:42 by yooh              #+#    #+#             */
/*   Updated: 2023/01/05 15:54:55 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child_process(t_global *global, int i,
				int pipe_count, t_token *token);
static void	execute_parent_process(t_global *global, pid_t pid,
				pid_t *pid_list, int i);

static int	handle_builtin(t_token *token, t_global *global, int *i)
{
	if (ft_strncmp(token->cmd_info[0], "exit", -1) == 0)
		exit(builtin_exit(global, token->cmd_info));
	if (!handle_redirect_stdin(token, global))
	{
		*i += 1;
		global->status = 1;
		return (1);
	}
	if (is_unprintable_builtin(token->cmd_info))
	{
		global->status = run_unprintable_builtin(global, token->cmd_info);
		*i += 1;
		return (1);
	}
	return (0);
}

void	run_pipelines(t_global *global, char **pipelines,
			int pipe_count, pid_t *pid_list)
{
	int			i;
	t_token		*token;
	pid_t		pid;

	i = 0;
	setsignal_ignored();
	while (pipelines[i])
	{
		parse_dollars(&pipelines[i], global);
		token = tokenize_input(pipelines[i]);
		if (token == NULL)
			break ;
		if (handle_builtin(token, global, &i))
			continue ;
		pipe(global->fds.fd);
		pid = fork();
		if (pid == 0)
			execute_child_process(global, i, pipe_count, token);
		execute_parent_process(global, pid, pid_list, i);
		i++;
		free_token(token);
	}
	dup2(global->fds.stdin_fd, STDIN_FILENO);
	dup2(global->fds.stdout_fd, STDOUT_FILENO);
}

void	kill_zombie_process(int pipe_count, t_global *global, pid_t *pid_list)
{
	int			i;
	int			status;

	i = 0;
	while (i < pipe_count)
	{
		waitpid(pid_list[i], &status, 0);
		if (i == pipe_count - 1)
			global->status = status;
		if (global->last_pid == pid_list[i])
		{
			if ((status & 0177) != 0 && (status & 0177) != 0177)
			{
				global->status = status & 0177;
				if (global->status == SIGQUIT && printf("^\\Quit: 3\n"))
					global->status = SIGQUIT + 128;
			}
			else
				global->status = (status >> 8) & 0xff;
		}
		dup2(global->fds.stdin_fd, STDIN_FILENO);
		i++;
	}
}

static void	execute_child_process(t_global *global, int i,
				int pipe_count, t_token *token)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(global->fds.fd[0]);
	handle_redirect_stdout(token, i, pipe_count, global->fds);
	close(global->fds.fd[1]);
	execute_cmd(global, token->cmd_info);
}

static void	execute_parent_process(t_global *global, pid_t pid,
				pid_t *pid_list, int i)
{
	close(global->fds.fd[1]);
	dup2(global->fds.fd[0], STDIN_FILENO);
	close(global->fds.fd[0]);
	pid_list[i] = pid;
	global->last_pid = pid;
}
