/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:57:24 by yooh              #+#    #+#             */
/*   Updated: 2022/12/09 20:49:29 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_default(t_data *data, int argc, char **argv)
{
	data->in = open(argv[1], O_RDONLY, 0644);
	data->out = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	data->argc = argc;
	if (data->in == -1 || data->out == -1)
	{
		perror("");
		write(data->in, "", 0);
	}
	dup2(data->in, STDIN_FILENO);
}

void	do_child_things(t_data data, int i, char *cmd, char **env)
{
	char	**cmd_info;

	if (close(data.fd[0]) == -1)
		handle_error();
	if (i < data.argc - 2 && dup2(data.fd[1], STDOUT_FILENO) == -1)
		handle_error();
	else if (i == data.argc - 2 && (dup2(data.out, STDOUT_FILENO) == -1))
		handle_error();
	cmd_info = get_cmd_info(cmd, env);
	execve(cmd_info[0], cmd_info, env);
}

void	do_parent_things(int i, int argc, t_data *data)
{
	if (i < argc - 1)
	{
		wait(NULL);
		if (close(data->fd[1]) == -1)
			handle_error();
		if (dup2(data->fd[0], STDIN_FILENO) == -1)
			handle_error();
	}
}

void	default_pipe(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;
	pid_t	pid;

	set_default(&data, argc, argv);
	i = 2;
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
