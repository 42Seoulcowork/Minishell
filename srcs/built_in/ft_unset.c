#include "minishell.h"

void	ft_unset(t_env_node *head, char *key)
{
	if (key == NULL)
		return ;
	delete_node(head, key);
}
