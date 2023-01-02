/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:50:37 by dongglee          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/12/31 18:52:59 by dongglee         ###   ########.fr       */
=======
/*   Updated: 2022/12/31 17:07:31 by yooh             ###   ########.fr       */
>>>>>>> b26dae0ad7d2e5b074e29c8d30eb255d370f8c8f
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: remove before submitting.
#define FOR_BUILTIN_CHECK "run in builtin\n"

// TODO: Implemente functions related to environment variables

int	builtin_error_exit(const char *msg, int status_code)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	return (status_code);
}

int	builtin_echo(t_global *global, char **cmd)
{
	int		flag_newline;
	int		i;

	printf(FOR_BUILTIN_CHECK);
	(void)global;
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

int	builtin_pwd(t_global *global, char **cmd)
{
	char		*path;
	const int	size = 2046;

	printf(FOR_BUILTIN_CHECK);
	(void)global;
	(void)cmd;
	path = malloc(sizeof(char) * size);
	getcwd(path, size);
	printf("%s\n", path);
	free(path);
	return (0);
}

int	builtin_exit(t_global *global, char **cmd)
{
	int	i;

	printf(FOR_BUILTIN_CHECK);
	printf("exit\n");
	(void)global;
	i = 0;
	if (!cmd[1])
		return (0);
	if (cmd[2] != NULL)
		return (builtin_error_exit("exit: too many arguments\n", 1));
	i += cmd[1][i] == '-';
	if (ft_strlen(cmd[1]) > 9)
		return (builtin_error_exit(
				"exit: numeric argument required\n", 255));
	while (cmd[1][i])
		if (!ft_isdigit(cmd[1][i++]))
			return (builtin_error_exit(
					"exit: numeric argument required\n", 255));
	return (((unsigned)ft_atoi(cmd[1])) % 256);
}

int	builtin_cd(t_global *global, char **cmd)
{
	printf(FOR_BUILTIN_CHECK);
	(void)global;
	if (!cmd[1])
		return (0);
	if (chdir(cmd[1]) == 0)
		return (0);
	return (builtin_error_exit("cd: No such file or directory\n", 1));
}
