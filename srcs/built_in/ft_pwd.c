#include "minishell.h"

void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		path = ft_strjoin(path, "\n");
		ft_putstr_fd(path, STDOUT_FILENO);
		g_exit_status = 0;
	}
	else
	{
		ft_putstr_fd("minishell: pwd: no path\n", STDERR_FILENO);
		g_exit_status = 1;
	}
}
