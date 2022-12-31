/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:30:42 by yooh              #+#    #+#             */
/*   Updated: 2022/12/31 11:33:02 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_pipelines(char **pipelines, t_fds fds,
			int pipe_count, pid_t *pid_list)
{
	int			i;
	t_token		*token;
	pid_t		pid;

	i = 0;
	while (pipelines[i])
	{
		token = tokenize_input(pipelines[i]);
		if (token == NULL || (!handle_redirect_stdin(token, fds) && i++))
			break ;
		pipe(fds.fd);
		pid = fork();
		if (pid == 0)
		{
			close(fds.fd[0]);
			handle_redirect_stdout(token, i, pipe_count, fds);
			close(fds.fd[1]);
			execute_cmd(token->cmd_info, i, pipe_count);
		}
		close(fds.fd[1]);
		dup2(fds.fd[0], STDIN_FILENO);
		close(fds.fd[0]);
		pid_list[i++] = pid;
		free_token(token);
	}
	dup2(fds.stdin_fd, STDIN_FILENO);
	dup2(fds.stdout_fd, STDOUT_FILENO);
}

void	kill_zombie_process(int pipe_count, pid_t *pid_list, t_fds fds)
{
	int		i;
	int		status;

	i = 0;
	pid_list = 0;
	while (i < pipe_count)
	{
		//waitpid(pid_list[i], &status, 0);
		wait(&status);
		dup2(fds.stdin_fd, STDIN_FILENO);
		i++;
	}
}
