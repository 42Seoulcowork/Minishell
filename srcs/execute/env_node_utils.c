#include "minishell.h"
#include <assert.h> // TODO 지워야 함

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

	assert(key != NULL); // TODO 지워야 함
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

size_t	get_node_len(t_env_node *head)
{
	size_t	i;

	i = 0;
	head = head->next;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

char	**convert_array(t_env_node *head)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	**arr;

	i = 0;
	arr = malloc(sizeof(char *) * (get_node_len(head) + 1));
	head = head->next;
	while (head != NULL)
	{
		if (head->value)
		{
			tmp = ft_strjoin(head->key, "=");
			tmp2 = ft_strjoin(tmp, "\"");
			tmp3 = ft_strjoin(tmp2, head->value);
			arr[i] = ft_strjoin(tmp3, "\"");
			free(tmp);
			free(tmp2);
			free(tmp3);
		}
		else
			arr[i] = ft_strdup(head->key);
		head = head->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

t_env_node	*init_node(char **envp)
{
	int			i;
	char		**tmp;
	t_env_node	*tmp_node;
	t_env_node	*head_node;

	i = -1;
	head_node = create_node(NULL, NULL);
	tmp_node = head_node;
	while (envp[++i])
	{
		tmp = ft_split(envp[i], '=');
		if (!ft_strcmp(tmp[0], "OLDPWD"))
		{
			tmp[1] = NULL;
		}
		tmp_node->next = create_node(tmp[0], tmp[1]);
		tmp_node = tmp_node->next;
	}
	return (head_node);
}

void	add_node(t_env_node *head, t_env_node *node)
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	head->next = node;
}
