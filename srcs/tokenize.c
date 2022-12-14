/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 07:08:52 by yooh              #+#    #+#             */
/*   Updated: 2023/01/04 14:42:33 by yooh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_cmd(char *cmd, char *new);
static int	append_file_info(int cur_type, t_token *token, char *name);
static void	skip_space(char *input, t_tokenizing_info *info);

t_token	*tokenize_input(char *input)
{
	t_tokenizing_info	info;
	t_token				*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	ft_bzero(token, sizeof(t_token));
	ft_bzero(&info, sizeof(t_tokenizing_info));
	info.cmd = ft_calloc(1, 1);
	if (!parse_input_into_token(&info, input, token))
	{
		free(info.cmd);
		return (NULL);
	}
	if (!handle_prev_token_and_set(&info, token, input))
	{
		free(info.cmd);
		free(token);
		return (NULL);
	}
	token->cmd_info = split_cmd(info.cmd);
	free(info.cmd);
	return (token);
}

int	handle_prev_token_and_set(t_tokenizing_info *info,
				t_token *token, char *input)
{
	char	*temp;

	info->temp = ft_substr(input, info->start, info->i - info->start);
	if (info->cur_type == CMD)
	{
		temp = append_cmd(info->cmd, info->temp);
		free(info->cmd);
		free(info->temp);
		info->cmd = temp;
	}
	else
	{
		if (ft_strlen(info->temp) == 0)
		{
			printf("minishell: parse error\n");
			free(info->temp);
			return (0);
		}
		if (!append_file_info(info->cur_type, token, info->temp))
			return (0);
	}
	set_start_point(&info->start, &info->i, &info->cur_type, input);
	skip_space(input, info);
	return (1);
}

static void	skip_space(char *input, t_tokenizing_info *info)
{
	while (input[info->start] == ' ')
	{
		info->start++;
		info->i++;
	}
}

static int	append_file_info(int cur_type, t_token *token, char *name)
{
	t_list		*new;
	t_file_info	*file_info;
	char		*temp;

	if (name[0] == '\'')
		temp = ft_strtrim(name, "\'");
	else if (name[0] == '\"')
		temp = ft_strtrim(name, "\"");
	else
		temp = ft_strdup(name);
	free(name);
	file_info = (t_file_info *) malloc(sizeof(t_file_info));
	file_info->type = cur_type;
	file_info->filename = temp;
	new = ft_lstnew((void *) file_info);
	if (new == NULL || file_info == NULL)
		return (0);
	if (cur_type == REDIRECT_IN || cur_type == REDIRECT_HEREDOC)
		ft_lstadd_back(&(token->redirect_in), new);
	if (cur_type == REDIRECT_TRUNC_OUT || cur_type == REDIRECT_APPEND_OUT)
		ft_lstadd_back(&(token->redirect_out), new);
	return (1);
}

static char	*append_cmd(char *cmd, char *new)
{
	char	*temp;
	char	*space_temp;

	if (ft_strlen(new) == 0)
		return (ft_strdup(cmd));
	if (ft_strlen(cmd) == 0)
		return (ft_strdup(new));
	space_temp = ft_strjoin(cmd, " ");
	temp = ft_strjoin(space_temp, new);
	free(space_temp);
	return (temp);
}
