#include "minishell.h"

void	print_token(t_token *token)
{
	if (!token)
		return ;
	int i = 0;
	while (token->cmd && token->cmd[i])
	{
		printf("[%d] : \"%s\" (redir : %s)\n", i, token->cmd[i],
			(token->rdirs ? token->rdirs->file_name : "NULL"));
		i++;
	}
	t_redir *rdirs = token->rdirs;
	while (rdirs)
	{
		printf("[%d] : \"%s\" (redir : %s)\n", i, "",
			(rdirs->file_name ? rdirs->file_name : "NULL"));
		i++;
		rdirs = rdirs->next;
	}
	if (token->next)
		printf("\n");
}

void	print_queue(t_parsed_data *queue)
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
