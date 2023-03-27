#include "minishell.h"

void	init_data(t_parsed_data *data)
{
	data = (t_parsed_data *)malloc(sizeof(t_parsed_data));
	if (!data)
		return ;
	data->size = 0;
	data->front = NULL;
	data->rear = NULL;
}

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
	if (data->rear == NULL)
	{
		data->front = token;
		data->rear = token;
	}
	else
	{
		data->rear->next = token;
		data->rear = token;
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
