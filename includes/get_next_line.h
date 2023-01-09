/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utl.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donggyulee <donggyulee@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 10:14:12 by dongglee          #+#    #+#             */
/*   Updated: 2020/08/24 21:57:29 by donggyulee       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define OPEN_MAX 5000
# define R_SUCCESS 1
# define R_EOF 0
# define R_ERROR -1

int		get_next_line(int fd, char **line);
int		make_line(char **line, char *buff);

#endif
