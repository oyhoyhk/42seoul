/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:40:04 by yooh              #+#    #+#             */
/*   Updated: 2022/12/11 12:34:52 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/syslimits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

ssize_t	ft_gnllen(char *str);
char	*ft_gnl_strdup(char *str);
int		split_newline(char **left, ssize_t start, ssize_t length);
char	*get_next_line(int fd);
char	*read_line(char **arr, int fd, ssize_t read_count, char *result);
char	*ft_gnljoin(char **s1, char *s2, ssize_t s1_len, ssize_t s2_len);
char	*get_until_newline(char	**left);
int		free_buf(char *buf);
int		free_fd(char **arr, int fd);

#endif