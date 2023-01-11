/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:39:05 by dongglee          #+#    #+#             */
/*   Updated: 2023/01/11 13:48:28 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_error_return_code(const char *msg, int code)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	return (code);
}

int	start(t_global *global)
{
	(void)global;
	mlx_loop(global->mlx);
	return (0);
}

void destory(t_global *global)
{
	(void) global;
	/* TODO: free global */
}

int	main(int argc, char *argv[])
{
	t_global	global;

	ft_memset(&global, 0, sizeof(t_global));
	if (argc != 2)
		return (print_error_return_code("Argument Error\n", 1));
	if (init(&global, argv[1]))
		return (print_error_return_code("Map Error\n", 1));
	start(&global);
	exit_program(&global);
	return (0);
}
