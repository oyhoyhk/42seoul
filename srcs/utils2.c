/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:44:38 by yooh              #+#    #+#             */
/*   Updated: 2023/01/06 07:42:52 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	handle_special_case(char *input, t_global *global)
{
	char	*temp;

	if (ft_strncmp(input, "$", -1) == 0)
	{
		ft_putstr_fd("minishell > $: command not found\n", 2);
		global->status = 127;
		free(input);
		return (0);
	}
	if (ft_strncmp(input, "", -1) == 0)
	{
		free(input);
		return (0);
	}
	temp = ft_strtrim(input, " ");
	if (ft_strncmp(temp, "", -1) == 0)
	{
		add_history(input);
		free(input);
		free(temp);
		return (0);
	}
	free(temp);
	return (1);
}

void	cal_info(int *sing, int *doub, char ch)
{
	if (ch == '\'')
	{
		if (*doub == 1)
			return ;
		else
		{
			if (*sing == 1)
				*sing = 0;
			else
				*sing = 1;
		}
	}
	if (ch == '\"')
	{
		if (*sing == 1)
			return ;
		else
		{
			if (*doub == 1)
				*doub = 0;
			else
				*doub = 1;
		}
	}
}
