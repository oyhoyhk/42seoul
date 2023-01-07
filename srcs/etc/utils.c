/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:50:46 by yooh              #+#    #+#             */
/*   Updated: 2023/01/07 11:21:00 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_logo(void)
{
	printf(TM_RED);
	printf("\n");
	printf("                  .-')    ('-. .-. \n");
	printf("                 ( OO ). ( OO )  / \n");
	printf(" .---. .-----.  (_)---\\_),--. ,--. \n");
	printf("/_   |/  .-.  \\ /    _ | |  | |  | \n");
	printf(" |   |   \\_.' / \\  :` `. |   .|  | \n");
	printf(" |   |/  .-. '.  '..`''.)|       | \n");
	printf(" |   |  |   |  |.-._)   \\|  .-.  | \n");
	printf(" |   |\\  '-'  / \\       /|  | |  | \n");
	printf(" `---' `----''   `-----' `--' `--' \n");
	printf("\n");
	printf(TM_RESET);
}

int	free_2d_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (1);
}

int	is_path(const char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			return (TRUE);
		++i;
	}
	return (FALSE);
}

void	kill_zombie_process(int pipe_count, t_global *global, pid_t *pid_list)
{
	int			i;
	int			status;

	i = 0;
	while (i < pipe_count)
	{
		waitpid(pid_list[i], &status, 0);
		if (i == pipe_count - 1 && !global->flag)
			global->status = status;
		if (global->last_pid == pid_list[i] && !global->flag)
		{
			if ((status & 0177) != 0 && (status & 0177) != 0177)
			{
				if (global->status == 2 && printf("^C\n"))
					global->status = 2 + 128;
				if (global->status == SIGQUIT && printf("^\\Quit: 3\n"))
					global->status = SIGQUIT + 128;
			}
			else
				global->status = (status >> 8) & 0xff;
		}
		dup2(global->stdin_fd, STDIN_FILENO);
		global->flag = 0;
		i++;
	}
}

char	*new_file_name(void)
{
	static int		i;
	const char		*temp = "/Users/yooh/tmp/temp_18sh_";
	char			*num;
	char			*result;

	num = ft_itoa(i);
	result = ft_strjoin(temp, num);
	i++;
	free(num);
	return (result);
}
