/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subinlee <subinlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:34:19 by subinlee          #+#    #+#             */
/*   Updated: 2023/03/24 21:31:27 by subinlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// #include <stdio.h>

// int	main()
// {
// 	t_queue	q;
// 	t_cmdline	c1;
// 	t_cmdline	c2;
// 	t_cmdline	c3;

// 	init_queue(&q);

// 	c1.path = "ls";
// 	c1.cmd = (char **)malloc(sizeof(char *) * 3);
// 	c1.cmd[0] = "ls";
// 	c1.cmd[1] = "a";
// 	c1.cmd[2] = "l";
// 	c1.rdr.type = "<<";
// 	c1.rdr.file_name = "a";

// 	c2.path = "grep";
// 	c2.cmd = (char **)malloc(sizeof(char *) * 2);
// 	c2.cmd[0] = "grep";
// 	c2.cmd[1] = "\"\"";

// 	c3.path = "cat";
// 	c3.cmd = (char **)malloc(sizeof(char *) * 1);
// 	c3.cmd[0] = "cat";

// 	enqueue(&q, c1);
// 	enqueue(&q, c2);
// 	enqueue(&q, c3);

// 	printf("*** ENQUEUE ***\n");
// 	printf("c1 path {%s}\n", c1.path);
// 	printf("c1 cmd {%s}->{%s}->{%s}\n", c1.cmd[0], c1.cmd[1], c1.cmd[2]);
// 	printf("c1 rdr type {%s}\n", c1.rdr.type);
// 	printf("c1 rdr file name {%s}\n", c1.rdr.file_name);
// 	printf("\n");
// 	printf("c2 path {%s}\n", c2.path);
// 	printf("c2 cmd {%s}->{%s}\n", c2.cmd[0], c2.cmd[1]);
// 	printf("c2 rdr type {%s}\n", c2.rdr.type);
// 	printf("c2 rdr file name {%s}\n", c2.rdr.file_name);
// 	printf("\n");
// 	printf("c3 path {%s}\n", c3.path);
// 	printf("c3 cmd {%s}\n", c3.cmd[0]);
// 	printf("c3 rdr type {%s}\n", c3.rdr.type);
// 	printf("c3 rdr file name {%s}\n", c3.rdr.file_name);

// 	dequeue(&q);
// 	dequeue(&q);

// 	printf("*** DEQUEUE ***\n");
// 	printf("c1 path {%s}\n", c1.path);
// 	printf("c1 cmd {%s}->{%s}->{%s}\n", c1.cmd[0], c1.cmd[1], c1.cmd[2]);
// 	printf("c1 rdr type {%s}\n", c1.rdr.type);
// 	printf("c1 rdr file name {%s}\n", c1.rdr.file_name);
// 	printf("\n");
// 	printf("c2 path {%s}\n", c2.path);
// 	printf("c2 cmd {%s}->{%s}\n", c2.cmd[0], c2.cmd[1]);
// 	printf("c2 rdr type {%s}\n", c2.rdr.type);
// 	printf("c2 rdr file name {%s}\n", c2.rdr.file_name);
// 	printf("\n");
// 	printf("c3 path {%s}\n", c3.path);
// 	printf("c3 cmd {%s}\n", c3.cmd[0]);
// 	printf("c3 rdr type {%s}\n", c3.rdr.type);
// 	printf("c3 rdr file name {%s}\n", c3.rdr.file_name);

// 	return (0);
// }