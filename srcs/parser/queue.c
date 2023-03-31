#include "minishell.h"



void	enqueue(t_p_data *data, t_token *token)
{
	if (data->front == NULL)
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

t_token	*dequeue(t_p_data *data)
{
	t_token	*token_tmp;

	if (data->size == 0)
		return (NULL);
	token_tmp = data->front;
	data->front = token_tmp->next;
	(data->size)--;
	return (token_tmp);
}
