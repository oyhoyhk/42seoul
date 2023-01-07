/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:24 by yooh              #+#    #+#             */
/*   Updated: 2023/01/07 06:53:52 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_global	*init(char *envp[])
{
	t_global		*global;
	struct termios	ter;

	global = (t_global *) malloc(sizeof(t_global));
	if (!global)
		return (NULL);
	bzero(global, sizeof(t_global));
	tcgetattr(STDIN_FILENO, &ter);
	ter.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &ter);
	setsignal();
	global->stdin_fd = dup(STDIN_FILENO);
	global->stdout_fd = dup(STDOUT_FILENO);
	global->envl = env_array_to_list(envp);
	return (global);
}

int	main(int argc, __attribute__((unused))char **argv, char *envp[])
{
	char		*input;
	t_list		*processes;
	t_global	*global;

	if (argc != 1)
	{
		printf("Too Many Arguments!\n");
		exit(1);
	}
	print_logo();
	global = init(envp);
	while (1)
	{
		input = readline("minishell > ");
		if (input == NULL)
			return (1);
		if (ft_strlen(input) == 0)
			continue ;
		add_history(input);
		processes = parse(global, input);
		handle_pipes(global, processes);
		ft_lstclear(&processes, process_destory);
		free(input);
	}
	return (0);
}
