/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:54:24 by yooh              #+#    #+#             */
/*   Updated: 2022/12/09 20:41:40 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_heredoc_string(int count)
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

void	read_from_stdin(int fd[2], pid_t pid, char *word, int argc)
{
	char	*result;
	char	*heredoc_str;

	if (pid == 0)
	{
		while (1)
		{
			heredoc_str = get_heredoc_string(argc - 5);
			write(1, heredoc_str, ft_strlen(heredoc_str));
			result = get_next_line(0);
			if (!result || ft_strncmp(result, word, ft_strlen(word)) == 0)
				break ;
			write(fd[1], result, ft_strlen(result));
			free(result);
		}
		exit(0);
	}
	wait(NULL);
	if (close(fd[1]) == -1 || dup2(fd[0], STDIN_FILENO) == -1)
		handle_error();
}

static void	heredoc_setting(t_data *data, int temp_fd[2], int argc, char **argv)
{
	if (pipe(temp_fd) == -1)
		handle_error();
	data->out = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (data->out == -1)
		handle_error();
	if (pipe(temp_fd) == -1)
		handle_error();
	data->argc = argc;
}

void	heredoc(int argc, char **argv, char **env)
{
	int		i;
	pid_t	pid;
	t_data	data;
	int		temp_fd[2];

	if (argc < 5)
		handle_error();
	heredoc_setting(&data, temp_fd, argc, argv);
	pipe(temp_fd);
	pid = fork();
	if (pid == -1)
		handle_error();
	read_from_stdin(temp_fd, pid, argv[2], argc);
	i = 3;
	while (i < argc - 1)
	{
		pipe(data.fd);
		pid = fork();
		if (pid == 0)
			do_child_things(data, i, argv[i], env);
		do_parent_things(i, argc, &data);
		i++;
	}
}
