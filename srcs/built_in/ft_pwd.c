#include "minishell.h"

void	ft_pwd(t_env_node *head)
{
	char	*path;
	char 	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp)
	{
		path = ft_strjoin_s(tmp, "\n");
		free(tmp);
		ft_putstr_fd(path, STDOUT_FILENO);
		g_exit_status = 0;
	}
	else
	{
		tmp = ft_getenv(head, "PWD");
		path = ft_strjoin_s(tmp, "\n");
		free(tmp);
		ft_putstr_fd(path, STDOUT_FILENO);
		g_exit_status = 0;
	}
}
