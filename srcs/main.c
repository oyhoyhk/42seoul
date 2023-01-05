/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongglee <dongglee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:15:24 by yooh              #+#    #+#             */
/*   Updated: 2023/01/05 21:09:17 by dongglee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pipe list -> token list -> token

void	print_info(void *content)
{
	t_token *token;

	token = (t_token *)content;
	printf("%d ", token->type);
	printf("%s@\n", token->str);
}

int	main(int argc, char **argv, char *envp[])
{
	char	*input;
	t_list	*tokens;

	if (argc != 1)
	{
		printf("Too Many Arguments!\n");
		exit(1);
	}
	while (1)
	{
		input = readline("minishell > ");
		if (input == NULL)
			return (1);
		if (ft_strlen(input) == 0)
			continue ;
		add_history(input);
		tokens = parse(input);
		ft_lstiter(tokens, print_info);
		ft_lstclear(&tokens, token_destory);
		free(input);
	}
	return (0);
}
