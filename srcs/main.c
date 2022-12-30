/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:24 by yooh              #+#    #+#             */
/*   Updated: 2022/12/30 17:05:35 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char *envp[])
{
	t_global		global;
	struct termios	ter;

	/*** need to remove ***/
	(void)envp;
	(void)argv;
	/*** need to remove ***/
	bzero(&global, sizeof(t_global));
	tcgetattr(STDIN_FILENO, &ter);
	ter.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &ter);
	setsignal();
	global.fds.stdin_fd = dup(STDIN_FILENO);
	global.fds.stdout_fd = dup(STDOUT_FILENO);
	if (argc != 1)
	{
		printf("Too Many Arguments!\n");
		exit(1);
	}
	start_read(global);
	return (0);
}
