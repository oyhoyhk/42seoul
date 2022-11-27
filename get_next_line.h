/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:40:04 by yooh              #+#    #+#             */
/*   Updated: 2022/11/27 14:10:43 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/syslimits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

ssize_t	ft_strlen(char *str);
char	*ft_strdup(char *str);
int		split_newline(char **left, ssize_t start, ssize_t length);
char	*get_next_line(int fd);
char	*read_line(char **arr, int fd, ssize_t read_count, char *result);
char	*ft_strjoin(char **s1, char *s2, ssize_t s1_len, ssize_t s2_len);
char	*get_until_newline(char	**left);
int		free_buf(char *buf);
int		free_fd(char **arr, int fd);

#endif