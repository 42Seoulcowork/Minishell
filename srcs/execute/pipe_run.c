#include "minishell.h"

static void	fd_handler(int fds[], t_envp *tenvp)
{
	close(fds[READ_END]);
	close(fds[WRITE_END]);
	dup2(tenvp->stdin_dup, STDIN_FILENO);
	dup2(tenvp->stdout_dup, STDOUT_FILENO);
	close(tenvp->stdin_dup);
	close(tenvp->stdout_dup);
}

static int	working_pid(t_envp *tenvp)
{
	int		fds[2];
	pid_t	pid;
	int		i;
	int		status;

	i = -1;
	while (++i < tenvp->argc)
	{
		if (pipe(fds) == -1)
			error(PIPE_ERROR, "pipe", tenvp);
		if (tenvp->exit_status)
			break ;
		pid = fork();
		if (pid == -1)
			error(FORK_ERROR, "fork", tenvp);
		if (pid == 0)
		{
			if (i < tenvp->argc - 1)
			{
				dup2(fds[WRITE_END], STDOUT_FILENO);
				close(fds[WRITE_END]);
				close(fds[READ_END]);
			}
			work_pid(i, tenvp);
		}
		else
		{
			if (i == tenvp->argc - 1)
			{
				if (waitpid(pid, &status, 0) == -1)
					error(RUN_ERROR, "pid", tenvp);
			}
			else
			{
				if (waitpid(pid, &status, WNOHANG) == -1)
					error(RUN_ERROR, "pid", tenvp);
				dup2(fds[READ_END], STDIN_FILENO);
				close(fds[READ_END]);
				close(fds[WRITE_END]);
			}
		}
	}
	fd_handler(fds, tenvp);
	return (status);
}

static int	argv_len(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	pipex(char *str, t_envp *tenvp)
{
	int i;
	int	status;

	tenvp->argv = ft_split(str, '|');
	tenvp->argc = argv_len(tenvp->argv);
	i = -1;
	while (++i < tenvp->argc)
		tenvp->argv[i] = ft_strtrim(tenvp->argv[i], " 	");
	tenvp->stdin_dup = dup(STDIN_FILENO); // TODO dup도 오류 처리를 해주긴 해야할텐데...
	tenvp->stdout_dup = dup(STDOUT_FILENO); // TODO dup도 오류 처리를 해주긴 해야할텐데...
	status = working_pid(tenvp);
	if (WIFEXITED(status))
		tenvp->exit_status = WEXITSTATUS(status);
	else // TODO 시그널에 의해 종료되었거나 강제 종료되었을 때 처리가 필요함
	{
		if (WIFSIGNALED(status))
		{
			ft_putnbr_fd(WTERMSIG(status), 2);
			ft_putstr_fd("  시그널에 의한 비정상 종료\n", 2);
		}
		else if (WIFSTOPPED(status))
		{
			ft_putnbr_fd(WSTOPSIG(status), 2);
			ft_putstr_fd("  강제 종료에 의한 비정상 종료\n", 2);
		}
		else
			ft_putstr_fd("하하하 왜 에러일까요, 알아맞춰주세요\n", 2);
	}
}
