/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:37:25 by yooh              #+#    #+#             */
/*   Updated: 2022/12/28 20:03:21 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_heredoc_string(int count)
{
	char	*base;
	int		i;
	char	*temp;
	char	*result;

	base = ft_strdup("heredoc> ");
	result = "heredoc> ";
	temp = "pipe ";
	i = 0;
	while (i < count)
	{
		result = ft_strjoin(temp, base);
		free(base);
		base = result;
		i++;
	}
	free(base);
	return (result);
}

void	read_from_stdin(int fd[2], char *word, int pipe_count, t_fds fds)
{
	char	*result;
	char	*heredoc_str;
	pid_t	pid;

	pipe(fd);
	pid = fork();
	heredoc_str = get_heredoc_string(pipe_count - 1);
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			write(fds.stdout_fd, heredoc_str, ft_strlen(heredoc_str));
			result = get_next_line(fds.stdin_fd);
			if (!result || ft_strncmp(result, word, ft_strlen(result) - 1) == 0)
				break ;
			write(fd[1], result, ft_strlen(result));
			free(result);
		}
		exit(0);
	}
	wait(NULL);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
}

static void	execute_readline(char *input, t_fds fds)
{
	int		i;
	int		pipe_count;
	pid_t	*pid_list;
	char	**execution_list;

	execution_list = ft_split(input, '|');
	i = 0;
	pipe_count = count_pipe(execution_list);
	pid_list = (pid_t *) malloc(sizeof(pid_t) * (pipe_count));
	run_pipelines(execution_list, fds, pipe_count, pid_list);
	dup2(fds.stdin_fd, STDIN_FILENO);
	close(fds.fd[0]);
	close(fds.fd[1]);
	kill_zombie_process(pipe_count, pid_list, fds);
	free(pid_list);
	free_2d_arr(execution_list);
}

void	start_read(t_fds fds)
{
	char	*input;

	while (1)
	{
		input = readline("minishell > ");
		if (input == NULL)
		{
			printf("you should terminate shell\n");
			return ;
		}
		add_history(input);
		execute_readline(input, fds);
		free(input);
		system("leaks minishell");
	}
}
