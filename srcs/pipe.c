/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:30:42 by yooh              #+#    #+#             */
/*   Updated: 2022/12/29 08:49:40 by yooh             ###   ########.fr       */
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
		//show_token(token);
		if (!handle_redirect_stdin(token, fds) && i++)
			break ;
		pipe(fds.fd);
		handle_redirect_stdout(token, i, pipe_count, fds);
		pid = fork();
		if (pid == 0)
			execute_cmd(token->cmd_info, i, pipe_count, fds);
		pid_list[i] = pid;

		close(fds.fd[1]);
		close(fds.fd[0]);
		i++;
		free_token(token);
	}
}

void	kill_zombie_process(int pipe_count, pid_t *pid_list, t_fds fds)
{
	int		i;
	int		status;

	i = 0;
	while (i < pipe_count)
	{
		waitpid(pid_list[i], &status, 0);
		dup2(fds.stdin_fd, STDIN_FILENO);
		i++;
	}
}
