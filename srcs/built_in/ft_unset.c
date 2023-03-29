#include "minishell.h"

void	ft_unset(t_env_node *head, char *key)
{
	delete_node(head, key);
}
