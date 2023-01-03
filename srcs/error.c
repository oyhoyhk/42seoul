/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 07:23:33 by yooh              #+#    #+#             */
/*   Updated: 2023/01/03 11:49:56 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_syntax_error(void)
{
	ft_putstr_fd("minishell: syntax error\n", 2);
	return (1);
}

void	print_valid_error(const char *cmd, const char *id)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(id, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}
