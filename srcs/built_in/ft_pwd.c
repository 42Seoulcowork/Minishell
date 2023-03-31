#include "minishell.h"

void	ft_pwd(t_env_node *head)
{
	char *path;

	path = getcwd(NULL, 0);
	if (path)
	{
		path = ft_strjoin(path, "\n");
		ft_putstr_fd(path, STDOUT_FILENO);
		head->value = "0";
	}
	else
	{
		ft_putstr_fd("minishell: pwd: no path\n", STDERR_FILENO);
		head->value = "1";
	}
}
