#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "includes/minishell.h"

t_token	tokenize_input(char *input)
{
	char	**list;
	int		i;
	char	*pos;
	t_token	result;

	ft_bzero(&result, sizeof(t_token));
	list = ft_split(input, ' ');
	i = 0;
	while (list[i])
	{
		pos = ft_strchr(input, '>');
	}
}

int main(void)
{
	int fd;

	fd = open("infile", O_RDONLY, 0644);
	dup2(fd, STDIN_FILENO);
	char *str = "/bin/cat -e";
	char **result = ft_split(str, ' ');
	execve(result[0], result, NULL);
}