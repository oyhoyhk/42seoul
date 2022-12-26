/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:24 by yooh              #+#    #+#             */
/*   Updated: 2022/12/26 14:12:46 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_open_redirection(char **result)
{
	int		fd;
	const char	*arg_error = "minishell: parse error near '\n'";
	const char	*open_error = "minishell: no such file or directory: ";

	printf("redirection!\n");
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
	printf("let's dup2!\n");
	dup2(fd, STDIN_FILENO);
}

void	excute_cmd(char *input, int i, int count, t_fds fds)
{
	char	**result;

	result = ft_split(input, ' ');
	close(fds.fd[0]);
	if (i + 1 == count)
		dup2(fds.stdout_fd, STDOUT_FILENO);
	else
		dup2(fds.fd[1], STDOUT_FILENO);
	result = get_cmd_info(input);
	if (ft_strncmp(result[0], "<", -1) == 0)
	{
		handle_open_redirection(result);
		char	**temp;
		int		length;
		int		idx;
		length = 0;
		idx = 2;
		while (result[idx])
		{
			idx++;
			length++;
		}
		temp = (char **) malloc(sizeof(char *) * (length + 1));
		idx = 0;
		while (idx < length)
		{
			temp[idx] = result[idx + 2];
			idx++;
		}
		temp[idx] = NULL;
		execve(create_absolute_route(temp[0]), temp, NULL);
	}
	execve(result[0], result, NULL);
	
}

void		serial_excution(char *cmd_string, t_fds fds)
{
	char	**cmd_list;
	int		i;
	int		count;
	pid_t	*pid_list;
	int		status;
	pid_t	pid;
	
	cmd_list = ft_split(cmd_string, '|');
	count = 0;
	i = 0;
	while (cmd_list[count])
		count++;
	pid_list = (pid_t *) malloc(sizeof(pid_t) * (count));
	while (cmd_list[i])
	{
		pipe(fds.fd);
		pid = fork();
		if (pid == 0)
			excute_cmd(cmd_list[i], i, count, fds);
		pid_list[i] = pid;
		close(fds.fd[1]);
		if (i + 1 < count)
			dup2(fds.fd[0], STDIN_FILENO);
		i++;
	}
	dup2(fds.stdin_fd, STDIN_FILENO);
	close(fds.fd[0]);
	close(fds.fd[1]);
	i = 0;
	status = 0;
	while (i < count)
	{
		waitpid(pid_list[i], &status, 0);
		dup2(fds.stdin_fd, STDIN_FILENO);
		i++;
	}
}

int	start_read(t_fds fds)
{
	char	*input;
	char	**serial_list;
	int		i;

	input = readline("minishell > ");
	if (input == NULL)
	{
		printf("you should terminate shell\n");
		return 0;
	}
	add_history(input);

	i = -1;
	serial_list = ft_split(input, ';');
	while (serial_list[++i])
		serial_excution(serial_list[i], fds);
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