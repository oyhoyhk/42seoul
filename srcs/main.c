/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:24 by yooh              #+#    #+#             */
/*   Updated: 2022/12/28 17:31:29 by yooh             ###   ########.fr       */
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

int	handle_redirect_stdin(t_token *token, int pipe_count, t_fds fds)
{
	t_list	*cur;
	int		in_fd;
	int		fd[2];
	pid_t	pid;

	cur = token->redirect_in;
	while (cur)
	{
		if (((t_file_info *)cur->content)->type == REDIRECT_IN)
		{
			in_fd = open(((t_file_info *)cur->content)->filename, O_RDONLY, 0644);
			if (in_fd == -1)
			{
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
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		else
		{
			dup2(fds.stdin_fd, STDIN_FILENO);
			read_from_stdin(fd, ((t_file_info *)cur->content)->filename, pipe_count, fds);
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
	//dup2(fds.stdout_fd, STDOUT_FILENO);
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
		//show_token(token);
		if (!handle_redirect_stdin(token, pipe_count, fds))
		{
			i++;
			continue;
		}
		handle_redirect_stdout(token, fds);
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

int	main(int argc, char **argv, char *envp[])
{
	t_fds			fds;
	struct termios	ter;

	/*** need to remove ***/
	(void)envp;
	(void)argv;
	/*** need to remove ***/

	tcgetattr(STDIN_FILENO, &ter);
	ter.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &ter);
	setsignal();
	fds.stdin_fd = dup(STDIN_FILENO);
	fds.stdout_fd = dup(STDOUT_FILENO);

	if (argc != 1)
	{
		printf("Too Many Arguments!\n");
		exit(1);
	}
	while (1)
	{
		if (start_read(fds) == 0)
			break ;
	}
	return (0);
}