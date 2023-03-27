#include "minishell.h"

void	print_token(t_token *token)
{
	if (!token)
		return ;
	while (token)
	{
		int i = 0;
		while (token->cmd && token->cmd[i])
		{
			printf("%s ", token->cmd[i]);
			i++;
		}
		t_redir *rdirs = token->rdirs;
		while (rdirs)
		{
			if (rdirs->redir_type == RE_INPUT)
				printf("<%s ", rdirs->file_name);
			else if (rdirs->redir_type == RE_OUTPUT)
				printf(">%s ", rdirs->file_name);
			else if (rdirs->redir_type == RE_APPEND)
				printf(">>%s ", rdirs->file_name);
			rdirs = rdirs->next;
		}
		if (token->next)
			printf("| ");
		token = token->next;
	}
	printf("\n");
}

void print_queue(t_parsed_data *queue)
{
	if (queue == NULL)
		return ;
	t_token *tmp = queue->front;
	while (tmp != NULL)
	{
		print_token(tmp);
		tmp = tmp->next;
	}
}
