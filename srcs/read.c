/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:10:13 by yooh              #+#    #+#             */
/*   Updated: 2023/01/07 11:04:52 by yooh             ###   ########.fr       */
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
		ft_putstr_fd("> ", global->stdout_fd);
		result = get_next_line(global->stdin_fd);
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
	if (global->status == 512)
	{
		global->status = 1;
		global->flag = 1;
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
