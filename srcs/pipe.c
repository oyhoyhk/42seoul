/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:30:42 by yooh              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/02 13:37:41 by dongglee         ###   ########.fr       */
=======
/*   Updated: 2022/12/31 17:05:18 by yooh             ###   ########.fr       */
>>>>>>> b26dae0ad7d2e5b074e29c8d30eb255d370f8c8f
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_pipelines(t_global *global, char **pipelines, t_fds fds,
			int pipe_count, pid_t *pid_list)
{
	int			i;
	t_token		*token;
	pid_t		pid;

	i = 0;
	setsignal_ignored();
	while (pipelines[i])
	{
		token = tokenize_input(pipelines[i]);
		if (ft_strncmp(token->cmd_info[0], "exit", -1) == 0)
			exit(builtin_exit(global, token->cmd_info));
		if (token == NULL || (!handle_redirect_stdin(token, fds) && i++))
			break ;
		pipe(fds.fd);
		pid = fork();
		if (pid == 0)
		{
			close(fds.fd[0]);
			handle_redirect_stdout(token, i, pipe_count, fds);
			close(fds.fd[1]);
			execute_cmd(global, token->cmd_info, i, pipe_count);
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
