#include "minishell.h"

void	ft_unset(t_env_node *head, char **keys)
{
	int	i;

	i = 1;
	if (keys[1] == NULL)
		return ;
	while (keys[i] != NULL)
	{
		delete_node(head, keys[i]);
		++i;
	}
}
