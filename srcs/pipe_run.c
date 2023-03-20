#include "minishell.h"

static void	working_pid(t_envp tenvp)
{
	int		fds[2];
	pid_t	pid_1;
	pid_t	pid_2;
	int		i;

	i = -1;
	while (++i < tenvp.argc - 1)
	{
		if (pipe(fds) == -1)
			error(PIPE_ERROR, "pipe");
		pid_1 = fork();
		if (pid_1 == -1)
			error(FORK_ERROR, "fork");
		else if (pid_1 == 0)
		{
			close(fds[READ_END]);
			dup2(fds[WRITE_END], STDOUT_FILENO);
			work_pid(i, tenvp);
			close(fds[WRITE_END]);
			exit(0);
		}
		else
		{
			pid_2 = fork();
			if (pid_2 == -1)
				error(FORK_ERROR, "fork");
			else if (pid_2 == 0)
			{
				close(fds[WRITE_END]);
				dup2(fds[READ_END], STDIN_FILENO);
				work_pid(i + 1, tenvp);
				close(fds[READ_END]);
				exit(0);
			}
			else
			{
				close(fds[0]);
				close(fds[1]);
				waitpid(pid_1, NULL, 0);
				waitpid(pid_2, NULL, 0);
			}
		}
	}
}

static int	argv_len(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	pipex(char *str, t_envp tenvp)
{
	int		i;

	tenvp.argv = ft_split(str, '|');
	tenvp.argc = argv_len(tenvp.argv);
	i = -1;
	while (++i < tenvp.argc)
		tenvp.argv[i] = ft_strtrim(tenvp.argv[i], " 	");
	working_pid(tenvp);
	return (EXIT_SUCCESS);
}

