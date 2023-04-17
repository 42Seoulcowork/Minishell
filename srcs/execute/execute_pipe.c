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
		signal(SIGINT, signal_handler_for_parent);
		wait(status);
		signal(SIGINT, signal_handler);
		handle_execute_exit_status(*status);
		/* TODO
		 * 현재 execute.c 파일에 있는 execute_p_data()함수 마지막 동작도 exit status 처리임.
		 * 근데, 파이프가 없으면서 외장함수이면 status처리를 두 번 하게 됨.
		 *
		 * built-in은 따로 exit status를 함수로 처리하지 않기에 저 함수가 필요없어서
		 * execute_p_data() 함수에서 먼저 종료되도록 설정되어있음.
		 *
		 * 그렇다면 이 중복 동작을 방지하기 위해 두 가지 방법이 있음.
		 *
		 * 1. 현재 함수 부분의 handle_execute_exit_status()를 살리고 execute_p_data()함수에서
		 * pipe가 없을 때 바로 종료시키기
		 * 2. 현재 함수 부분의 handle_execute_exit_status()를 없애고 execute_p_data()함수 현행 유지
		 *
		 * 근데 어떤 영향을 미칠지 몰라서 우선 주석으로 적어두고 실행부끼리 상의해봐여
		 * @gyuhong, @subinlee
		 */
	}
	else if (pid == 0)
	{
		if (p_data->front->cmd_type == EXTERN_FUNC)
			ft_signal_child();
		flag = execute_token(head, p_data->front, FALSE);
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
		ft_signal_child();
		close(fd[0][READ_END]);
		dup2(fd[0][WRITE_END], STDOUT_FILENO);
		close(fd[0][WRITE_END]);
		execute_token(head, p_data->front, TRUE);
		exit(g_exit_status);
	}
	else if (pid > 0)
	{
		signal(SIGINT, signal_handler_for_parent);
		close(fd[0][WRITE_END]);
		p_data->front = p_data->front->next;
	}
}

static void	do_child(t_env_node *head, t_p_data *p_data, int **fd, int i)
{
	ft_signal_child();
	close(fd[i][READ_END]);
	dup2(fd[i - 1][READ_END], STDIN_FILENO);
	close(fd[i - 1][READ_END]);
	dup2(fd[i][WRITE_END], STDOUT_FILENO);
	close(fd[i][WRITE_END]);
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
		if (pid == 0)
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
		ft_signal_child();
		dup2(fd[i][READ_END], STDIN_FILENO);
		close(fd[i][READ_END]);
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
