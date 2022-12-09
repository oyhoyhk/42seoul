/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 07:07:44 by yooh              #+#    #+#             */
/*   Updated: 2022/12/09 20:32:49 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line.h"
# include <string.h>
# include <stdio.h>
# include <errno.h>

# define NO_FD			1
# define MALLOC_FAILED	2
# define NO_COMMAND		3
# define COMMAND_FAILED	4
# define ARGUE_ERROR	5

typedef struct s_data
{
	int		in;
	int		out;
	int		fd[2];
	int		argc;
}	t_data;

char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *string);
char	**create_path_list(char **env);
char	*check_cmd_valid(char *full_cmd, char **path_list);
void	ft_bzero(void *s, size_t n);
void	free_2d_arr(void **arr);
char	**get_cmd_info(char *cmd, char **env);
void	*ft_calloc(size_t nmeb, size_t size);
char	*get_cmd(char *str, char **path_list);
char	*read_file(char *filename);
void	heredoc(int argc, char **argv, char **env);
void	default_pipe(int argc, char **argv, char **env);
void	set_default(t_data *data, int argc, char **argv);
void	do_child_things(t_data data, int i, char *cmd, char **env);
void	do_parent_things(int i, int argc, t_data *data);
void	handle_error(void);
#endif