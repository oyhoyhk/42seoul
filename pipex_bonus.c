/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bous.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 06:44:25 by yooh              #+#    #+#             */
/*   Updated: 2022/12/13 07:39:35 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc < 4)
		handle_error();
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
		heredoc(argc, argv, env);
	else
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
