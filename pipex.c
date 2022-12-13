/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 07:09:44 by yooh              #+#    #+#             */
/*   Updated: 2022/12/14 06:36:10 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
	{
		write(2, "Only Needs 4 Arguments\n",
			ft_strlen("Only Needs 4 Arguments\n"));
		exit(1);
	}
	default_pipe(argc, argv, env);
	return (0);
}

char	**get_cmd_arr(char *raw_cmd, char **path_list)
{
	char	*cmd;
	char	**result;

	cmd = get_cmd(raw_cmd, path_list);
	result = ft_split(cmd, ' ');
	if (!result)
		handle_error();
	return (result);
}

void	handle_error(void)
{
	perror("");
	exit(1);
}
