/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:11:12 by yooh              #+#    #+#             */
/*   Updated: 2022/12/31 15:22:58 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(char **list)
{
	int		i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}

static void	handle_redirect_in(int *start, int *i, int *cur_type, char *input)
{
	*cur_type = REDIRECT_IN;
	*start = *i + 1;
	if (input[*i + 1] == '<')
	{
		*cur_type = REDIRECT_HEREDOC;
		*start = *i + 2;
		*i += 1;
	}
}

void	set_start_point(int	*start, int *i, int *cur_type, char *input)
{
	if (input[*i] == ' ')
	{
		*cur_type = CMD;
		*start = *i + 1;
	}
	if (input[*i] == '<')
		handle_redirect_in(start, i, cur_type, input);
	if (input[*i] == '>')
	{
		*cur_type = REDIRECT_TRUNC_OUT;
		*start = *i + 1;
		if (input[*i + 1] == '>')
		{
			*cur_type = REDIRECT_APPEND_OUT;
			*start = *i + 2;
			*i += 1;
		}
	}
}
