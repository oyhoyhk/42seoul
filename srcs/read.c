/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:37:25 by yooh              #+#    #+#             */
/*   Updated: 2023/01/06 07:42:41 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_file_open_error(void)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		ft_putstr_fd("", fd[0]);
		exit(0);
	}
	wait(NULL);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	return (0);
}

static void	handle_read_stdin(t_global *global, char *word, int fd[2])
{
	char	*result;

	signal(SIGINT, exit);
	while (1)
	{
		ft_putstr_fd("> ", global->fds.stdout_fd);
		result = get_next_line(global->fds.stdin_fd);
		if (!result || (ft_strlen(result) != 1
				&& ft_strncmp(result, word, ft_strlen(word)) == 0
				&& result[ft_strlen(word)] == '\n'))
			break ;
		ft_putstr_fd(result, fd[0]);
		free(result);
	}
	exit(0);
}

void	read_from_stdin(char *word, t_global *global, int status)
{
	pid_t		pid;
	int			fd[2];
	const char	*filename = new_file_name();

	fd[0] = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
		handle_read_stdin(global, word, fd);
	waitpid(pid, &status, 0);
	global->status = status;
	if (status == 512)
	{
		global->status = 1;
		handle_file_open_error();
		printf("\n");
	}
	else
	{
		fd[1] = open(filename, O_RDWR, 0644);
		dup2(fd[1], STDIN_FILENO);
	}
	free((void *)filename);
}

static int	input_valid_check(char *input)
{
	int		sing;
	int		doub;
	int		i;

	sing = 0;
	doub = 0;
	i = 0;
	while (input[i])
	{
		cal_info(&sing, &doub, input[i]);
		i++;
	}
	if (sing || doub)
		return (0);
	return (1);
}

void	execute_readline(t_global *global, char *input)
{
	int		i;
	int		pipe_count;
	pid_t	*pid_list;
	char	**execution_list;

	if (!input_valid_check(input))
		return ;
	execution_list = parse_readline(input);
	if (execution_list == NULL)
	{
		ft_putstr_fd("minishell: parse error\n", STDERR_FILENO);
		global->status = 1;
		return ;
	}
	i = 0;
	pipe_count = count_pipe(execution_list);
	pid_list = (pid_t *) malloc(sizeof(pid_t) * (pipe_count));
	run_pipelines(global, execution_list, pipe_count, pid_list);
	dup2(global->fds.stdin_fd, STDIN_FILENO);
	close(global->fds.fd[0]);
	close(global->fds.fd[1]);
	kill_zombie_process(pipe_count, global, pid_list);
	free(pid_list);
	free_2d_arr(execution_list);
	setsignal();
}
