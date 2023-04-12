#include "minishell.h"

static void	run_builtin(t_env_node *head, t_token *token, int child)
{
	if (token->cmd_type == ECHO_FUNC)
		ft_echo(token->cmd);
	else if (token->cmd_type == CD_FUNC)
		ft_cd(head, token->cmd);
	else if (token->cmd_type == PWD_FUNC)
		ft_pwd(head);
	else if (token->cmd_type == EXPORT_FUNC)
		ft_export(head, token->cmd);
	else if (token->cmd_type == UNSET_FUNC)
		ft_unset(head, token->cmd);
	else if (token->cmd_type == ENV_FUNC)
		ft_env(head);
	else if (token->cmd_type == EXIT_FUNC)
		ft_exit(token->cmd, child);
}

int	execute_token(t_env_node *head, t_token *token, int child)
{
	if (token->redir != NULL)
	{
		if (handle_redir(token->redir) == FALSE)
		{
			g_exit_status = 1;
			return (FALSE);
		}
	}
    if (token->cmd == NULL)
        return (FALSE);
	if (token->cmd_type != EXTERN_FUNC)
		run_builtin(head, token, child);
	else
		run_cmd(head, token);
	return (TRUE);
}

void	handle_execute_errror(int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else // TODO 시그널에 의해 종료되었거나 강제 종료되었을 때 처리가 필요함
	{
		g_exit_status = 130;
		// TODO 주영이한테 물어봐요 규선, 명준, 수빈
		if (WIFSIGNALED(status))
			ft_putnbr_fd(WTERMSIG(status), STDERR_FILENO);
		else if (WIFSTOPPED(status))
			ft_putnbr_fd(WSTOPSIG(status), STDERR_FILENO);
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
		fd = malloc_s(sizeof(int *) * p_data->pipe_cnt);
		while (i < p_data->pipe_cnt)
		{
			fd[i] = malloc_s(sizeof(int) * 2);
			++i;
		}
		execute_first_pipe(head, p_data, fd);
		i = execute_middle_pipe(head, p_data, fd);
		status = execute_end_pipe(head, p_data, fd, i);
		i = 0;
		while (i < p_data->pipe_cnt)
		{
			free(fd[i]);
			++i;
		}
		free(fd);
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
