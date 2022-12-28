/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:24 by yooh              #+#    #+#             */
/*   Updated: 2022/12/28 12:40:21 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_open_redirection(char **result)
{
	int		fd;
	const char	*arg_error = "minishell: parse error near '\n'";
	const char	*open_error = "minishell: no such file or directory: ";

	if (result[1] == NULL)
	{
		write(2, arg_error, ft_strlen(arg_error));
		exit(1);
	}
	fd = open(result[1], O_RDONLY, 0644);
	if (fd == -1)
	{
		write(2, open_error, ft_strlen(open_error));
		write(2, result[1], ft_strlen(result[1]));
		write(2, "\n", 1);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
}

void	excute_cmd(char **cmd, int i, int count, t_fds fds)
{
	char	*absolute_route;

	close(fds.fd[0]);
	if (i + 1 == count)
		dup2(fds.stdout_fd, STDOUT_FILENO);
	else
		dup2(fds.fd[1], STDOUT_FILENO);
	absolute_route = create_absolute_route(cmd[0]);
	if (absolute_route == NULL)
	{
		//명령어 없음
		exit(1);
	}
	free(cmd[0]);
	cmd[0] = absolute_route;
	execve(cmd[0], cmd, NULL);
}

void		handle_redirect_stdin(t_token *token, int pipe_count, t_fds fds)
{
	t_list	*cur;
	int		in_fd;
	pid_t	pid;
	int		fd[2];

	cur = token->redirect_in;
	while (cur)
	{
		if (((t_file_info *)cur->content)->type == REDIRECT_IN)
		{
			in_fd = open(((t_file_info *)cur->content)->filename, O_RDONLY, 0644);
			if (in_fd == -1)
			{
				// read failed
				return ;
			}
			printf("in_fd : %d\n", in_fd);
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
			
		}
		else
		{
			pipe(fd);
			pid = fork();
			read_from_stdin(fd, pid, ((t_file_info *)cur->content)->filename, pipe_count);
		}
		fds.stdin_fd++;
		fds.stdin_fd--;
		cur = cur->next;
		//dup2(fds.stdin_fd, STDIN_FILENO);
	}
}

void		serial_excution(char *input, t_fds fds)
{
	int		i;
	int		pipe_count;
	pid_t	*pid_list;
	int		status;
	pid_t	pid;
	char	**excution_list;
	t_token	*token;
	
	excution_list = ft_split(input, '|');
	pipe_count = 0;
	i = 0;
	while (excution_list[pipe_count])
		pipe_count++;
	pid_list = (pid_t *) malloc(sizeof(pid_t) * (pipe_count));
	while (excution_list[i])
	{
		token = tokenize_input(excution_list[i]);
		show_token(token);
		handle_redirect_stdin(token, pipe_count, fds);
		pipe(fds.fd);
		pid = fork();
		if (pid == 0)
			excute_cmd(token->cmd_info, i, pipe_count, fds);
		pid_list[i] = pid;
		close(fds.fd[1]);
		if (i + 1 < pipe_count)
			dup2(fds.fd[0], STDIN_FILENO);
		i++;
	}
	dup2(fds.stdin_fd, STDIN_FILENO);
	close(fds.fd[0]);
	close(fds.fd[1]);
	i = 0;
	status = 0;
	while (i < pipe_count)
	{
		waitpid(pid_list[i], &status, 0);
		dup2(fds.stdin_fd, STDIN_FILENO);
		i++;
	}
}

int	start_read(t_fds fds)
{
	char	*input;

	input = readline("minishell > ");
	if (input == NULL)
	{
		printf("you should terminate shell\n");
		return 0;
	}
	add_history(input);
	serial_excution(input, fds);
	return (1);
}

int	main(int argc, char **argv)
{
	t_fds	fds;

	fds.stdin_fd = dup(STDIN_FILENO);
	fds.stdout_fd = dup(STDOUT_FILENO);

	if (argc != 1)
	{
		printf("Too Many Arguments!\n");
		exit(1);
	}
	*argv = 0;
	while (1)
	{
		if (start_read(fds) == 0)
			break ;
	}
	return (0);
}