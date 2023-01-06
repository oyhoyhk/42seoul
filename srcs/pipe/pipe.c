/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:56:50 by yooh              #+#    #+#             */
/*   Updated: 2023/01/06 21:14:06 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child_process(t_global *global, int i,
				int pipe_count, t_process *token);
static void	execute_parent_process(t_global *global, pid_t pid,
				pid_t *pid_list, int i);

static int	handle_builtin(t_process *token, t_global *global)
{
	char	**cmd_info;

	cmd_info = parse_list_to_arr2d(token->cmd_info);
	if (cmd_info[0] && ft_strncmp(cmd_info[0], "exit", -1) == 0)
		exit(builtin_exit(global, cmd_info));
	if (!handle_redirect_stdin(token, global))
	{
		global->flag = 1;
		global->status = 1;
		return (1);
	}
	if (cmd_info[0] && is_unprintable_builtin(cmd_info))
	{
		global->status = run_unprintable_builtin(global, cmd_info);
		return (1);
	}
	return (0);
}

void	execute_each_process(t_list *processes, t_global *global,
			int *count, pid_t *pid_list)
{
	t_list	*cur;
	pid_t	pid;

	cur = processes;
	while (cur)
	{	
		if (handle_builtin((t_process *)cur->content, global))
		{
			cur = cur->next;
			continue ;
		}
		pipe(global->fd);
		pid = fork();
		if (pid == 0)
			execute_child_process(global, *count, ft_lstsize(processes),
				(t_process *)cur->content);
		execute_parent_process(global, pid, pid_list, *count);
		(*count) += 1;
		cur = cur->next;
	}
}

void	handle_pipes(t_global *global, t_list *processes)
{
	t_list	*cur;
	int		i;
	pid_t	*pid_list;

	cur = processes;
	i = 0;
	pid_list = (pid_t *) malloc(sizeof(pid_t) * ft_lstsize(processes));
	setsignal_ignored();
	execute_each_process(processes, global, &i, pid_list);
	kill_zombie_process(ft_lstsize(processes), global, pid_list);
	free(pid_list);
	dup2(global->stdin_fd, STDIN_FILENO);
	dup2(global->stdout_fd, STDOUT_FILENO);
}

static void	execute_child_process(t_global *global, int i,
				int pipe_count, t_process *token)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(global->fd[0]);
	handle_redirect_stdout(token, i, pipe_count, global);
	close(global->fd[1]);
	execute_cmd(global, token->cmd_info);
}

static void	execute_parent_process(t_global *global, pid_t pid,
				pid_t *pid_list, int i)
{
	close(global->fd[1]);
	dup2(global->fd[0], STDIN_FILENO);
	close(global->fd[0]);
	pid_list[i] = pid;
	global->last_pid = pid;
}
