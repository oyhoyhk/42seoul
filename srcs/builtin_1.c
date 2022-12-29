/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:50:37 by dongglee          #+#    #+#             */
/*   Updated: 2022/12/29 16:50:35 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: remove before submitting.
#define FOR_BUILTIN_CHECK "run in builtin\n"

// TODO: Implemente functions related to environment variables

int	builtin_echo(char **cmd)
{
	int		flag_newline;
	int		i;

	printf(FOR_BUILTIN_CHECK);
	i = 1;
	flag_newline = TRUE;
	if (ft_strncmp(cmd[i], "-n", 3) == 0)
	{
		++i;
		flag_newline = FALSE;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i++]);
		if (cmd[i])
			printf(" ");
		else
			break ;
	}
	if (flag_newline)
		printf("\n");
	return (0);
}

int	builtin_pwd(char **cmd)
{
	char		*path;
	const int	size = 2046;

	printf(FOR_BUILTIN_CHECK);
	if (cmd[1])
	{
		perror("pwd: too many arguments\n");
		return (1);
	}
	path = malloc(sizeof(char) * size);
	getcwd(path, size);
	printf("%s\n", path);
	free(path);
	return (0);
}

int	builtin_exit(char **cmd)
{
	int	i;

	printf(FOR_BUILTIN_CHECK);
	if (cmd[1])
	{
		if (cmd[2] != NULL)
		{
			perror("exit: too many arguments\n");
			return (1);
		}
		i = 0;
		if (cmd[1][i] == '-')
			++i;
		while (cmd[1][i])
		{
			if (!ft_isdigit(cmd[1][i++]))
			{
				perror("exit: numeric argument required\n");
				return (255);
			}
		}
		return (((unsigned)ft_atoi(cmd[1])) % 256);
	}
	return (0);
}

int	builtin_cd(char **cmd)
{
	if (!cmd[1])
		return (0);
	if (chdir(cmd[1]) == 0)
		return (0);
	perror("cd: Noa a directory\n");
	return (1);
}