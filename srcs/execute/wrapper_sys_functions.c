#include "minishell.h"

int	ft_pipe(int fd[2])
{
	int	error_check;

	error_check = pipe(fd);
	if (error_check == -1)
	{
		g_exit_status = 1;
		perror("pipe");
		return (FALSE);
	}
	return (TRUE);
}

int	ft_fork(void)
{
	int	error_check;

	error_check = fork();
	if (error_check == -1)
	{
		g_exit_status = 1;
		perror("fork");
		return (error_check);
	}
	return (error_check);
}
