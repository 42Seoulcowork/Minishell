#include "minishell.h"

t_token	*create_token(char **cmd, t_redir *rdirs)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->cmd = cmd;
	token->rdirs = rdirs;
	token->next = NULL;
	return (token);
}

void	enqueue(t_parsed_data *data, t_token *token)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = data->front;
	if (data->rear == NULL)
	{
		data->front = token;
		data->rear = token;
	}
	else
	{
		while (++i < data->size)
			tmp = tmp->next;
		tmp->next = token;
//		data->rear = token;
//		data->rear->next = token;
	}
	data->size++;
}

t_token	*tokendequeue(t_parsed_data *data)
{
	t_token	*token_tmp;

	if (data->size == 0)
		return (NULL);
	token_tmp = data->front;
	data->front = token_tmp->next;
	(data->size)--;
	return (token_tmp);
}
