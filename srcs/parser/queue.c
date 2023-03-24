/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subinlee <subinlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:34:19 by subinlee          #+#    #+#             */
/*   Updated: 2023/03/24 22:13:26 by subinlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

// Header에 추가

typedef struct	s_rdr
{
	char	*type;
	char	*file_name;
}	t_rdr;

typedef struct	s_cmdline // TODO 파싱 구조 설계
{
	char			*path;
	char			**cmd;
	struct s_rdr	rdr;
}	t_cmdline;

typedef struct	s_node
{
	struct s_cmdline	cmdline;
	// struct s_node		*prev; // TODO 단방향으로 일단 구현함
	struct s_node		*next;
}	t_node;

typedef struct s_queue
{
	int				size;
	struct s_node	*front;
	struct s_node	*rear;
}	t_queue;

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

int	main()
{
	int			i;
	t_node		*tmp;
	t_queue		q;
	t_cmdline	c1;
	t_cmdline	c2;
	t_cmdline	c3;

	init_queue(&q);

	c1.path = "ls";
	c1.cmd = (char **)malloc(sizeof(char *) * 4);
	c1.cmd[0] = "ls";
	c1.cmd[1] = "a";
	c1.cmd[2] = "l";
	c1.cmd[3] = NULL; // TODO
	c1.rdr.type = "<<";
	c1.rdr.file_name = "a";

	c2.path = "grep";
	c2.cmd = (char **)malloc(sizeof(char *) * 3);
	c2.cmd[0] = "grep";
	c2.cmd[1] = "\"\"";
	c2.cmd[2] = NULL; // TODO

	c3.path = "cat";
	c3.cmd = (char **)malloc(sizeof(char *) * 2);
	c3.cmd[0] = "cat";
	c3.cmd[1] = NULL; // TODO

	enqueue(&q, c1);
	enqueue(&q, c2);
	enqueue(&q, c3);

	tmp = q.front;
	while (tmp)
	{
		printf("PATH: {%s}\n", tmp->cmdline.path);
		printf("CMD: ");
		i = 0;
		while(tmp->cmdline.cmd[i])
		{
			printf("{%s}->", tmp->cmdline.cmd[i]);
			i++;
		}
		printf("{NULL}\n");
		printf("RDR TYPE: {%s}\n", tmp->cmdline.rdr.type);
		printf("RDR FILE NAME: {%s}\n", tmp->cmdline.rdr.file_name);
		printf("\n");
		tmp = tmp->next;
	}

	dequeue(&q);
	dequeue(&q);

	printf("\n");
	tmp = q.front;
	while (tmp)
	{
		printf("PATH: {%s}\n", tmp->cmdline.path);
		printf("CMD: ");
		i = 0;
		while(tmp->cmdline.cmd[i])
		{
			printf("{%s}->", tmp->cmdline.cmd[i]);
			i++;
		}
		printf("{NULL}\n");
		printf("RDR TYPE: {%s}\n", tmp->cmdline.rdr.type);
		printf("RDR FILE NAME: {%s}\n", tmp->cmdline.rdr.file_name);
		printf("\n");
		tmp = tmp->next;
	}

	return (0);
}