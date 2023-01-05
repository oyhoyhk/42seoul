/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:37:25 by yooh              #+#    #+#             */
/*   Updated: 2023/01/05 08:22:07 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_from_stdin(char *word, t_fds fds, int status)
{
	char	*result;
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			ft_putstr_fd("> ", fds.stdout_fd);
			result = get_next_line(fds.stdin_fd);
			if (!result || (ft_strlen(result) != 1
					&& ft_strncmp(result, word, ft_strlen(word)) == 0
					&& result[ft_strlen(word)] == '\n'))
				break ;
			ft_putstr_fd(result, fd[1]);
			free(result);
		}
		exit(0);
	}
	waitpid(pid, &status, 0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
}

static void	cal_info(int *sing, int *doub, char ch)
{
	if (ch == '\'')
	{
		if (*doub == 1)
			return ;
		else
		{
			if (*sing == 1)
				*sing = 0;
			else
				*sing = 1;
		}
	}
	if (ch == '\"')
	{
		if (*sing == 1)
			return ;
		else
		{
			if (*doub == 1)
				*doub = 0;
			else
				*doub = 1;
		}
	}
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

static void	execute_readline(t_global *global, char *input)
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

void	start_read(t_global *global)
{
	char	*input;
	char	*trimmed_input;

	while (1)
	{
		input = readline("minishell > ");
		if (input == NULL)
			return ;
		trimmed_input = ft_strtrim(input, " ");
		if (ft_strlen(trimmed_input) == 0)
		{
			free(trimmed_input);
			free(input);
			continue ;
		}
		add_history(input);
		execute_readline(global, input);
		free(input);
		free(trimmed_input);
	}
}
