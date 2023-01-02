/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:30:42 by yooh              #+#    #+#             */
/*   Updated: 2023/01/02 21:01:57 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_pipelines(t_global *global, char **pipelines, t_fds fds,
			int pipe_count, pid_t *pid_list)
{
	int			i;
	t_token		*token;
	pid_t		pid;
	char		*line;

	i = 0;
	setsignal_ignored();
	while (pipelines[i])
	{
		line = handle_dollar(pipelines[i], global);
		free(pipelines[i]);
		pipelines[i] = line;
		token = tokenize_input(pipelines[i]);
		if (token == NULL)
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			break ;
		}
		if (ft_strncmp(token->cmd_info[0], "exit", -1) == 0)
			exit(builtin_exit(global, token->cmd_info));
		if (!handle_redirect_stdin(token, fds))
		{
			i++;
			global->status = 1;
			continue;
		}
		if (is_unprintable_builtin(token->cmd_info))
		{
			run_unprintable_builtin(global, token->cmd_info);
			++i;
			continue ;
		}
		pipe(fds.fd);
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			close(fds.fd[0]);
			handle_redirect_stdout(token, i, pipe_count, fds);
			close(fds.fd[1]);
			execute_cmd(global, token->cmd_info, i, pipe_count);
		}
		close(fds.fd[1]);
		dup2(fds.fd[0], STDIN_FILENO);
		close(fds.fd[0]);
		pid_list[i++] = pid;
		global->last_pid = pid;
		free_token(token);
	}
	dup2(fds.stdin_fd, STDIN_FILENO);
	dup2(fds.stdout_fd, STDOUT_FILENO);
}

void	kill_zombie_process(int pipe_count, t_global *global, pid_t *pid_list)
{
	int		i;
	int		status;

	i = 0;
	while (i < pipe_count)
	{
		wait(&status);
		if (global->last_pid == pid_list[pipe_count - 1])
			global->status = status % 255;
		dup2(global->fds.stdin_fd, STDIN_FILENO);
		i++;
	}
}
