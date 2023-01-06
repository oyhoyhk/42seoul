/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:24 by yooh              #+#    #+#             */
/*   Updated: 2023/01/06 07:42:28 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_read(t_global *global)
{
	char	*input;

	while (1)
	{
		input = readline("minishell > ");
		if (input == NULL)
			return ;
		if (!handle_special_case(input, global))
			continue ;
		add_history(input);
		execute_readline(global, input);
		free(input);
	}
}

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

	if (argc != 1 && *argv)
	{
		printf("Too Many Arguments!\n");
		exit(1);
	}
	global = (t_global *) malloc(sizeof(t_global));
	if (global == NULL)
		return (1);
	init(global, envp);
	print_logo();
	start_read(global);
	return (0);
}
