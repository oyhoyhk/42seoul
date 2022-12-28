/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_stdin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:37:25 by yooh              #+#    #+#             */
/*   Updated: 2022/12/28 10:56:59 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_heredoc_string(int count)
{
	char	*base;
	int		i;
	char	*temp;
	char	*result;

	base = ft_strdup("heredoc> ");
	result = "heredoc> ";
	temp = "pipe ";
	i = 0;
	while (i < count)
	{
		result = ft_strjoin(temp, base);
		free(base);
		base = result;
		i++;
	}
	free(base);
	return (result);
}

void	read_from_stdin(int fd[2], pid_t pid, char *word, int argc)
{
	char	*result;
	char	*heredoc_str;

	if (pid == 0)
	{
		while (1)
		{
			heredoc_str = get_heredoc_string(argc - 5);
			write(1, heredoc_str, ft_strlen(heredoc_str));
			result = get_next_line(STDIN_FILENO);
			if (!result || ft_strncmp(result, word, ft_strlen(result) - 1) == 0)
				break ;
			write(fd[1], result, ft_strlen(result));
			free(result);
		}
		exit(0);
	}
	wait(NULL);
	//if (close(fd[1]) == -1 || dup2(fd[0], STDIN_FILENO) == -1) 
	//	handle_error();
}