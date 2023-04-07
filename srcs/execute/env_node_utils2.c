#include "minishell.h"

t_env_node	*create_node(char *key, char *value)
{
	t_env_node	*new_node;

	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
		return (NULL);
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
	free(curr->key);
	free(curr->value);
	free(curr);
}

void	add_node(t_env_node *head, t_env_node *node)
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	head->next = node;
}
