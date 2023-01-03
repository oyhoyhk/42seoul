/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:23:07 by yooh              #+#    #+#             */
/*   Updated: 2023/01/03 07:25:08 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_dollars(char **origin, t_global *global)
{
	char	*temp;

	temp = handle_dollar(*origin, global);
	free(*origin);
	*origin = temp;
}
