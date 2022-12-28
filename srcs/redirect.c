/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:15:15 by yooh              #+#    #+#             */
/*   Updated: 2022/12/28 19:18:43 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_file_open_error(void);

int	handle_redirect_stdin(t_token *token, int pipe_count, t_fds fds)
{
	t_list	*cur;
	int		in_fd;
	int		fd[2];

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
			close(in_fd);
		}
		else
		{
			dup2(fds.stdin_fd, STDIN_FILENO);
			read_from_stdin(fd, ((t_file_info *)cur->content)->filename,
				pipe_count, fds);
		}
		cur = cur->next;
	}
	return (1);
}

void	handle_redirect_stdout(t_token *token, t_fds fds)
{
	t_list	*cur;
	int		fd;
	char	*file;
	int		type;

	cur = token->redirect_out;
	while (cur)
	{
		type = ((t_file_info *)(cur->content))->type;
		file = ((t_file_info *)(cur->content))->filename;
		if (type == REDIRECT_TRUNC_OUT)
			fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else
			fd = open(file, O_CREAT | O_APPEND | O_RDWR, 0644);
		dup2(fd, fds.stdout_fd);
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
		write(fd[0], "", 0);
		exit(0);
	}
	wait(NULL);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	return (0);
}
