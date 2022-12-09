/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 09:38:54 by yooh              #+#    #+#             */
/*   Updated: 2022/12/09 20:41:50 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path_from_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_strdup(env[i] + 5));
		i++;
	}
	return (NULL);
}

char	**create_path_list(char **env)
{
	char	**result;
	char	*path;

	path = get_path_from_env(env);
	if (path == NULL)
		handle_error();
	result = ft_split(path, ':');
	if (result == NULL)
		handle_error();
	free(path);
	return (result);
}

char	*get_cmd(char *str, char **path_list)
{
	char		*cmd;

	cmd = check_cmd_valid(str, path_list);
	return (cmd);
}
