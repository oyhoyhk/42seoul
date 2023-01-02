/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:24 by yooh              #+#    #+#             */
/*   Updated: 2023/01/02 13:08:39 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init(t_global *global, char *envp[])
{
	struct termios	ter;

	bzero(global, sizeof(t_global));
	tcgetattr(STDIN_FILENO, &ter);
	ter.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &ter);
	setsignal();
	global->fds.stdin_fd = dup(STDIN_FILENO);
	global->fds.stdout_fd = dup(STDOUT_FILENO);
	global->envl = env_array_to_list(envp);
}

int	main(int argc, char **argv, char *envp[])
{
	t_global		*global;

	/*** need to remove ***/
	(void)argv;
	/*** need to remove ***/
	if (argc != 1)
	{
		printf("Too Many Arguments!\n");
		exit(1);
	}
	global = (t_global *) malloc(sizeof(t_global));
	if (global == NULL)
		return (1);
	init(global, envp);
	start_read(global);
	return (0);
}
