/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooh <yooh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:11:12 by yooh              #+#    #+#             */
/*   Updated: 2023/01/03 12:45:55 by yooh             ###   ########.fr       */
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

int	parse_input_into_token(t_tokenizing_info *info,
				char *input, t_token *token)
{
	while (input[info->i])
	{
		if (input[info->i] == '\'' && info->in_single_quote)
			info->in_single_quote = FALSE;
		else if (input[info->i] == '\'' && !info->in_single_quote)
			info->in_single_quote = TRUE;
		if (input[info->i] == '\"' && info->in_double_quote)
			info->in_double_quote = FALSE;
		else if (input[info->i] == '\"' && !info->in_double_quote)
			info->in_double_quote = TRUE;
		if (ft_strchr(">< ", input[info->i]) && !info->in_double_quote
			&& !info->in_single_quote
			&& !handle_prev_token_and_set(info, token, input))
			return (0);
		(info->i)++;
	}
	return (1);
}

void	print_logo(void)
{
	printf("\n");
	printf("                  .-')    ('-. .-. \n");
	printf("                 ( OO ). ( OO )  / \n");
	printf(" .---. .-----.  (_)---\\_),--. ,--. \n");
	printf("/_   |/  .-.  \\ /    _ | |  | |  | \n");
	printf(" |   |   \\_.' / \\  :` `. |   .|  | \n");
	printf(" |   |/  .-. '.  '..`''.)|       | \n");
	printf(" |   |  |   |  |.-._)   \\|  .-.  | \n");
	printf(" |   |\\  '-'  / \\       /|  | |  | \n");
	printf(" `---' `----''   `-----' `--' `--' \n");
	printf("\n");
}
