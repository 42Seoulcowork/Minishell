#include "minishell.h"

static void	run_builtin(t_env_node *head, t_token *token)
{
	if (token->cmd_type == ECHO_FUNC)
		ft_echo(token->cmd);
	else if (token->cmd_type == CD_FUNC)
		ft_cd(head, token->cmd);
	else if (token->cmd_type == PWD_FUNC)
		ft_pwd();
	else if (token->cmd_type == EXPORT_FUNC)
		ft_export(head, token->cmd);
	else if (token->cmd_type == UNSET_FUNC)
		ft_unset(head, token->cmd);
	else if (token->cmd_type == ENV_FUNC)
		ft_env(head);
	else if (token->cmd_type == EXIT_FUNC)
		ft_exit(token->cmd);
}

void	execute_token(t_env_node *head, t_token *token)
{
	if (token->redir != NULL)
	{
		if (handle_redir(token->redir) == FALSE)
		{
			g_exit_status = 1;
			return ;
		}
	}
	if (token->cmd_type != EXTERN_FUNC)
		run_builtin(head, token);
	else
		run_cmd(head, token);
}

static void	handle_execute_errror(int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else // TODO 시그널에 의해 종료되었거나 강제 종료되었을 때 처리가 필요함
	{
		g_exit_status = 130;
		// TODO 주영이한테 물어봐요 규선, 명준, 수빈
		if (WIFSIGNALED(status))
		{
			ft_putnbr_fd(WTERMSIG(status), 2);
			ft_putstr_fd("  시그널에 의한 종료\n", 2);
		}
		else if (WIFSTOPPED(status))
		{
			// 130
			ft_putnbr_fd(WSTOPSIG(status), 2);
			ft_putstr_fd("  강제 종료에 의한 종료\n", 2);
		}
		else
			ft_putstr_fd("하하하 왜 에러일까요, 알아맞춰주세요\n", 2);
	}
}

void	execute_p_data(t_env_node *head, t_p_data *p_data, int i)
{
	int	**fd;
	int	status;

	if (p_data->pipe_cnt == 0)
	{
		if (execute_no_pipe(head, p_data, &status) == FALSE)
			return ;
		if (p_data->front->cmd_type != EXTERN_FUNC)
			return ;
	}
	else
	{
		fd = malloc(sizeof(int *) * p_data->pipe_cnt);
		while (i < p_data->pipe_cnt)
		{
			fd[i] = malloc(sizeof(int) * 2);
			++i;
		}
		execute_first_pipe(head, p_data, fd);
		i = execute_middle_pipe(head, p_data, fd);
		status = execute_end_pipe(head, p_data, fd, i);
	}
	handle_execute_errror(status);
}

void	execute(t_env_node *head, t_p_data *p_data)
{
	int	stdin_dup;
	int	stdout_dup;

	stdin_dup = dup(STDIN_FILENO);
	stdout_dup = dup(STDOUT_FILENO);
	execute_p_data(head, p_data, 0);
	dup2(stdin_dup, STDIN_FILENO);
	dup2(stdout_dup, STDOUT_FILENO);
	close(stdin_dup);
	close(stdout_dup);
	
}
