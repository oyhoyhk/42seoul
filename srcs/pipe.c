/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:30:42 by yooh              #+#    #+#             */
/*   Updated: 2022/12/29 07:51:33 by yooh             ###   ########.fr       */
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
		if (!handle_redirect_stdin(token, fds) && i++)
			continue ;
		handle_redirect_stdout(token, fds);
		pipe(fds.fd);
		pid = fork();
		if (pid == 0)
			execute_cmd(token->cmd_info, i, pipe_count, fds);
		pid_list[i] = pid;
		close(fds.fd[1]);
		if (i + 1 < pipe_count)
			dup2(fds.fd[0], STDIN_FILENO);
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
