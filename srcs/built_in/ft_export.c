#include "minishell.h"

static size_t	arr_len(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static t_env_node	*get_old_key_address(t_env_node *head, char *key)
{
	head = head->next;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

static char	**ft_simple_split(char *tmp, char *equal_address)
{
	char 	**str;
	int 	i;

	i = 0;
	str = malloc(sizeof(char*) * 3);
	while (tmp + i < equal_address)
	{

		++i;
	}
}

void	ft_export(t_env_node *head, char **cmd)
{
	int			i;
	char 		**arr;
	char 		*tmp;
	t_env_node	*old_key;

	i = 0;
	if (cmd[1] == NULL)
	{
		arr = convert_array(head);
		quick_sort(arr, 0, arr_len(arr) - 1);
		while (arr[i])
		{
			printf("declare -x %s\n", arr[i]);
			++i;
		}
		return ;
	}
	i = 1;
	while (cmd[i])
	{
		tmp = ft_strchr(cmd[i], '=');
		if (tmp == NULL)
		{
			old_key = get_old_key_address(head, cmd[i]);
			if (old_key == NULL)
				add_node(head, create_node(cmd[i], NULL));
			else
				old_key->value = "";
		}
		else
		{
			if (*(tmp + 1) != '\0')
			{
				old_key = get_old_key_address(head, cmd[i]);
				if (old_key == NULL)
					add_node(head, create_node(cmd[i], ""));
				else
					old_key->value = "";
			}
			else
			{
				*tmp = '\0';
				old_key = get_old_key_address(head, cmd[i]);
				if (old_key == NULL)
					add_node(head, create_node(cmd[i], ""));
				else
					old_key->value = "";
			}
		}
		++i;
	}
	/*
	tmp = ft_split(cmd[i], '=');
	old_key = get_old_key_address(head, tmp[0]);
	if (old_key == NULL)
		add_node(head, create_node(tmp[0], tmp[1]));
	else
		old_key->value = tmp[1];
	i++;
	*/
}
