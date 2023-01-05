/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:44:38 by yooh              #+#    #+#             */
/*   Updated: 2023/01/05 16:44:44 by yooh             ###   ########.fr       */
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