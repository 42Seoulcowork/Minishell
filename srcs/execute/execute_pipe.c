#include "minishell.h"

int	execute_no_pipe(t_env_node *head, t_p_data *p_data, int *status)
{
	int		flag;
	pid_t	pid;

	pid = 0;
	flag = TRUE;
	if (p_data->front->cmd != NULL && p_data->front->cmd_type == EXTERN_FUNC)
		pid = fork_s();
	if (pid > 0)
	{
		signal(SIGINT, signal_handler_2);
		wait(status);
		signal(SIGINT, signal_handler);
		handle_execute_errror(*status);
	}
	else if (pid == 0)
    {
        if (p_data->front->cmd_type != EXTERN_FUNC)
            signal(SIGINT, signal_handler_2);
		else
			ft_signal_default();
        flag = execute_token(head, p_data->front, FALSE);
		signal(SIGINT, signal_handler);
    }
	if (pid < 0 || flag == FALSE)
		return (FALSE);
	return (TRUE);
}

void	execute_first_pipe(t_env_node *head, t_p_data *p_data, int **fd)
{
	pid_t	pid;

	if (pipe_s(fd[0]) == FALSE)
		return ;
	pid = fork_s();
	if (pid == 0)
	{
		close(fd[0][READ_END]);
		dup2(fd[0][WRITE_END], STDOUT_FILENO);
		close(fd[0][WRITE_END]);
		ft_signal_default();
		execute_token(head, p_data->front, TRUE);
		exit(g_exit_status);
	}
	else if (pid > 0)
	{
		signal(SIGINT, signal_handler_2);
		close(fd[0][WRITE_END]);
		p_data->front = p_data->front->next;
	}
}

static void	do_child(t_env_node *head, t_p_data *p_data, int **fd, int i)
{
	close(fd[i][READ_END]);
	dup2(fd[i - 1][READ_END], STDIN_FILENO);
	close(fd[i - 1][READ_END]);
	dup2(fd[i][WRITE_END], STDOUT_FILENO);
	close(fd[i][WRITE_END]);
	ft_signal_default();
	execute_token(head, p_data->front, TRUE);
	exit(g_exit_status);
}

int	execute_middle_pipe(t_env_node *head, t_p_data *p_data, int **fd)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < p_data->pipe_cnt - 1)
	{
		++i;
		if (pipe_s(fd[i]) == FALSE)
			return (-1);
		pid = fork_s();
		if (pid == 0) // 자식
			do_child(head, p_data, fd, i);
		else if (pid > 0)
		{
			close(fd[i - 1][READ_END]);
			close(fd[i][WRITE_END]);
			p_data->front = p_data->front->next;
		}
		else
			return (-1);
	}
	return (i);
}

int	execute_end_pipe(t_env_node *head, t_p_data *p_data, int **fd, int i)
{
	int		tmp;
	int		status;
	pid_t	pid;

	pid = fork_s();
	status = 0;
	if (pid == 0)
	{
		dup2(fd[i][READ_END], STDIN_FILENO);
		close(fd[i][READ_END]);
		ft_signal_default();
		execute_token(head, p_data->front, TRUE);
		exit(g_exit_status);
	}
	else if (pid > 0)
	{
		close(fd[i][READ_END]);
		i = 0;
		while (i < p_data->pipe_cnt + 1)
		{
			if (pid == wait(&tmp))
				status = tmp;
			++i;
		}
		signal(SIGINT, signal_handler);
	}
	return (status);
}
