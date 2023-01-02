/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:37:25 by yooh              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/02 13:38:35 by dongglee         ###   ########.fr       */
=======
/*   Updated: 2022/12/31 20:05:42 by yooh             ###   ########.fr       */
>>>>>>> b26dae0ad7d2e5b074e29c8d30eb255d370f8c8f
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_from_stdin(char *word, t_fds fds)
{
	char	*result;
	pid_t	pid;
	int		fd[2];
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			ft_putstr_fd("> ", fds.stdout_fd);
			result = get_next_line(fds.stdin_fd);
			if (!result || (ft_strlen(result) != 1 &&
					ft_strncmp(result, word, ft_strlen(result) - 1) == 0))
				break ;
			ft_putstr_fd(result, fd[1]);
			free(result);
		}
		exit(0);
	}
	waitpid(pid, &status, 0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
}

static void	execute_readline(t_global *global, char *input)
{
	int		i;
	int		pipe_count;
	pid_t	*pid_list;
	char	**execution_list;

	execution_list = parse_readline(input);
	i = 0;
	pipe_count = count_pipe(execution_list);
	pid_list = (pid_t *) malloc(sizeof(pid_t) * (pipe_count));
	run_pipelines(global, execution_list, global->fds, pipe_count, pid_list);
	dup2(global->fds.stdin_fd, STDIN_FILENO);
	close(global->fds.fd[0]);
	close(global->fds.fd[1]);
	kill_zombie_process(pipe_count, pid_list, global->fds);
	setsignal();
	free(pid_list);
	free_2d_arr(execution_list);
}

void	start_read(t_global *global)
{
	char	*input;

	while (1)
	{
		input = readline("minishell > ");
		if (input == NULL)
			return ;
		if (ft_strlen(input) == 0)
			continue ;
		add_history(input);
		execute_readline(global, input);
		free(input);
	}
}
