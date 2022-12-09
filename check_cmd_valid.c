/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 10:48:41 by yooh              #+#    #+#             */
/*   Updated: 2022/12/09 20:46:07 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*create_absolute_address(char *path, char *full_cmd);
static void	free_strings(char **cmd_split, char *temp);

char	*check_cmd_valid(char *full_cmd, char **path_list)
{
	char	*result;

	while (*path_list)
	{
		result = create_absolute_address(*path_list, full_cmd);
		if (result)
			return (result);
		path_list++;
		free(result);
	}
	return (NULL);
}

static char	*create_absolute_address(char *path, char *full_cmd)
{
	char	*temp;
	char	*result;
	char	**cmd_split;
	char	*absolute_cmd;

	result = NULL;
	temp = ft_strjoin(path, "/");
	if (temp == NULL)
		handle_error();
	cmd_split = ft_split(full_cmd, ' ');
	if (cmd_split == NULL)
		handle_error();
	absolute_cmd = ft_strjoin(temp, cmd_split[0]);
	if (access(absolute_cmd, X_OK) == 0)
		result = ft_strjoin(temp, full_cmd);
	free(absolute_cmd);
	free_strings(cmd_split, temp);
	return (result);
}

static void	free_strings(char **cmd_split, char *temp)
{
	int		i;

	i = 0;
	while (cmd_split[i])
	{
		free(cmd_split[i]);
		i++;
	}
	free(cmd_split);
	free(temp);
}
