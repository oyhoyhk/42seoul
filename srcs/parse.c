#include "minishell.h"

// need to processing: [char], ['] ["] [>] [<] [|] [$]
// flag(int), token_buffer(t_list), env_buffer(t_list), type
// token list -> token

static void	add_process(t_list **processes)
{
	t_process	*process;

	process = malloc(sizeof(t_process));
	process->redirect_in = NULL;
	process->redirect_out = NULL;
	process->cmd_info = NULL;
	ft_lstadd_back(processes, ft_lstnew(process));
}

static void add_string_token(t_list **processes, t_list *cur)
{
	t_list		*last_process;
	t_process	*process;
	t_token		*token;

	if (*processes == NULL)
		add_process(processes);
	last_process = ft_lstlast(*processes);
	process = (t_process *)last_process->content;
	token = cur->content;
	ft_lstadd_back(&process->cmd_info, ft_lstnew(strdup(token->str)));
}

static int	get_type_redirect(const char *str)
{
	if (ft_strncmp(str, "<", 2) == 0)
		return (REDIRECT_IN);
	if (ft_strncmp(str, ">", 2) == 0)
		return (REDIRECT_TRUNC_OUT);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (REDIRECT_HEREDOC);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (REDIRECT_APPEND_OUT);
	return (-1);
}

static void	add_redirect_token(t_list **processes, t_list *cur)
{
	t_list		*last_process;
	t_process	*process;
	t_token		*token;
	t_file_info	*temp;

	if (*processes == NULL)
		add_process(processes);
	last_process = ft_lstlast(*processes);
	process = (t_process *)last_process->content;
	token = cur->content;
	temp = malloc(sizeof(t_file_info));
	temp->type = get_type_redirect(token->str);
	token = cur->next->content;
	temp->filename = ft_strdup(token->str);
	ft_lstadd_back(&process->redirect_in, ft_lstnew(temp));
}

static void add_process_token(t_list **processes, t_list *cur)
{
	(void) cur;
	if (*processes == NULL)
		add_process(processes);
	add_process(processes);
}

t_list	*make_parse_form(t_list *tokens)
{
	t_list	*cur;
	t_list	*ret;
	t_token	*token;

	ret = NULL;
	cur = tokens;
	while (cur)
	{
		token = cur->content;
		if (token->type == STRING)
			add_string_token(&ret, cur);
		else if (token->type == REDIRECT)
		{
			add_redirect_token(&ret, cur);
			cur = cur->next;
		}
		else if (token->type == PIPE)
			add_process_token(&ret, cur);
		cur = cur->next;
	}
	return (ret);
}

void	file_info_destory(void *ptr)
{
	t_file_info	*file_info;

	file_info = (t_file_info *)ptr;
	free(file_info->filename);
	file_info->filename = NULL;
	free(ptr);
}

void	process_destory(void *ptr)
{
	t_process	*process;

	process = (t_process *)ptr;
	ft_lstclear(&process->redirect_in, file_info_destory);
	ft_lstclear(&process->redirect_out, file_info_destory);
	ft_lstclear(&process->cmd_info, free);
	free(ptr);
}

t_list	*parse(const char *line)
{
	t_list	*tokens;
	t_list	*processes;

	tokens = NULL;
	if (lex(line, &tokens)
		|| validate_token(&tokens))
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		return (NULL);
	}
	processes = NULL;
	processes = make_parse_form(tokens);
	ft_lstclear(&tokens, token_destory);
	return (processes);
}
