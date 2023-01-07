/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:41:04 by yooh              #+#    #+#             */
/*   Updated: 2023/01/07 06:57:17 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_file_open_error(void);

int	handle_redirect_stdin(t_process *token, t_global *global)
{
	t_list	*cur;
	int		in_fd;

	cur = token->redirect_in;
	while (cur)
	{
		if (((t_file_info *)cur->content)->type == REDIRECT_IN)
		{
			in_fd = open(((t_file_info *)cur->content)->filename,
					O_RDONLY, 0644);
			if (in_fd == -1)
				return (handle_file_open_error());
			dup2(in_fd, STDIN_FILENO);
		}
		else
			read_from_stdin(((t_file_info *)cur->content)->filename, global, 0);
		cur = cur->next;
	}
	return (1);
}

void	handle_redirect_stdout(t_process *token, int i,
			int pipe_count, t_global *global)
{
	t_list	*cur;
	int		fd;
	char	*file;
	int		type;

	cur = token->redirect_out;
	if (i + 1 < pipe_count)
		dup2(global->fd[1], STDOUT_FILENO);
	else
		dup2(global->stdout_fd, STDOUT_FILENO);
	while (cur)
	{
		type = ((t_file_info *)(cur->content))->type;
		file = ((t_file_info *)(cur->content))->filename;
		if (type == REDIRECT_TRUNC_OUT)
			fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else
			fd = open(file, O_CREAT | O_APPEND | O_RDWR, 0644);
		dup2(fd, STDOUT_FILENO);
		cur = cur->next;
	}
}

static int	handle_file_open_error(void)
{
	int		fd[2];
	pid_t	pid;

	perror("");
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
