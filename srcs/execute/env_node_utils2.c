#include "minishell.h"

t_env_node	*create_node(char *key, char *value) //TODO create_node 이거 껍데기만 할당 했는데... 어떤건 할당한것을 넣고 어떤건 그냥 넣네? 이게 맞나...
{
	t_env_node	*new_node;

	new_node = malloc_s(sizeof(t_env_node));
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	delete_node(t_env_node *head, char *key)
{
	t_env_node	*prev;
	t_env_node	*curr;

	while (head->next != NULL)
	{
		if (ft_strcmp(head->next->key, key) == 0)
			break ;
		head = head->next;
	}
	if (head->next == NULL)
		return ;
	prev = head;
	curr = head->next;
	prev->next = curr->next;
	free_s(curr->key);
	free_s(curr->value);
	free_s(curr);
}

void	add_node(t_env_node *head, t_env_node *node)
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	head->next = node;
}
