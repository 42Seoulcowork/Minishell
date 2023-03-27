#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("type: %d ", tokens->type);
		printf("str: %s ", tokens->str);
		if (tokens->redir_file)
			printf("redir_file: %s ", tokens->redir_file);
		if (tokens->redir_type)
			printf("redir_type: %d", tokens->redir_type);
		printf("\n");
		tokens = tokens->next;
	}
}
