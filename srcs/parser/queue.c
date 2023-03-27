
#include "minishell.h"

void	init_queue(t_queue *queue)
{
	queue->size = 0;
	queue->front = NULL;
	queue->rear = NULL;
}

void	enqueue(t_queue *queue, t_cmdline cmdline)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return ;
	new->cmdline.path = cmdline.path;
	new->cmdline.cmd = cmdline.cmd;
	new->cmdline.rdr = cmdline.rdr;
	new->next = NULL;
	if (queue->size == 0)
		queue->front = new;
	else
		queue->rear->next = new;
	queue->rear = new;
	(queue->size)++;
}

t_cmdline	dequeue(t_queue *queue)
{
	t_node		*tmp_node;
	t_cmdline	tmp_cmdline;

	if (queue->size == 0)
		return (tmp_cmdline);
	tmp_node = queue->front;
	tmp_cmdline.path = tmp_node->cmdline.path;
	tmp_cmdline.cmd = tmp_node->cmdline.cmd;
	tmp_cmdline.rdr = tmp_node->cmdline.rdr;
	queue->front = tmp_node->next;
	free(tmp_node);
	(queue->size)--;
	return (tmp_cmdline);
}
