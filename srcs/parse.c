#include "minishell.h"

// need to processing: [char], ['] ["] [>] [<] [|] [$]
// flag(int), token_buffer(t_list), env_buffer(t_list), type
// token list -> token





t_list	*parse(const char *line)
{
	t_list	*tokens;

	tokens = filter(lex(line));
	if (tokens == NULL)
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
	return (tokens);
}
