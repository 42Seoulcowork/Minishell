#include "minishell.h"

static int	handle_redir(t_redir *redir)
{
	int fd;

	while (redir != NULL)
	{
		if (redir->type == RE_INPUT)
		{
			fd = open(redir->file_name, O_RDONLY);
			if (fd == -1) {
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->file_name, STDERR_FILENO);
				if (!access(redir->file_name, F_OK))
					ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
				else
					ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
				return (FALSE);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == RE_OUTPUT) // TODO 권한 줬다뺐다 해봐
		{
			if (access(redir->file_name, W_OK) && !access(redir->file_name, F_OK))
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->file_name, STDERR_FILENO);
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
				return (FALSE);
			}
			fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC , 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == RE_APPEND)
		{
			if (access(redir->file_name, W_OK) && !access(redir->file_name, F_OK))
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->file_name, STDERR_FILENO);
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
				return (FALSE);
			}
			fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	return (TRUE);
}

void	run_builtin(t_env_node *head, t_token *token)
{
	if (token->cmd_type == ECHO_FUNC)
		ft_echo(head, token->cmd);
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
		ft_exit(head, token->cmd);
}

void	execute_token(t_env_node *head, t_token *token)
{
	if (token->redir != NULL)
	{
		if (handle_redir(token->redir) == FALSE)
		{
			head->value = "1";
			return ;
		}
	}
	if (token->cmd_type != EXTERN_FUNC)
		run_builtin(head, token);
	else
		run_cmd(head, token);

}

void	execute(t_env_node *head, t_p_data *p_data)
{
	int	stdin_dup;
	int	stdout_dup;
	int *fd;
	int i;
	int	tmp;
	int status;
	pid_t pid;
	pid_t pid2;

	stdin_dup = dup(STDIN_FILENO);
	stdout_dup = dup(STDOUT_FILENO);
	i = 0;
	if (p_data->pipe_cnt == 0)
	{
		execute_token(head, p_data->front);
	}
	else
	{
		fd = malloc(sizeof(int) * 2 * p_data->pipe_cnt);
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			close(fd[READ_END]);
			dup2(fd[WRITE_END], STDOUT_FILENO);
			close(fd[WRITE_END]);
			execute_token(head, p_data->front);
		}
		else if (pid > 0)
		{
			p_data->front = p_data->front->next;
		}
		else
		{
			printf("fork error\n");
		}
		while (i < p_data->pipe_cnt - 1)
		{
			++i;
			pipe(fd + i * 2);//todo pipe error
			pid = fork();
			if (pid == 0) // 자식
			{
				close(fd[(i - 1) * 2 + 1]);
				close(fd[i * 2]);
				dup2(fd[(i - 1) * 2], STDIN_FILENO);
				dup2(fd[i * 2 + 1], STDOUT_FILENO);
				close(fd[(i - 1) * 2]);
				close(fd[i * 2 + 1]);
				execute_token(head, p_data->front);
			}
			else if (pid > 0)
			{
				p_data->front = p_data->front->next;
			}
			else
			{
				// error
			}
		}
		pid2 = fork();
		if (pid2 == 0) // 자식
		{
			close(fd[i * 2 + 1]);
			dup2(fd[i * 2], STDIN_FILENO);
			close(fd[i * 2]);
			execute_token(head, p_data->front);
		}
		else if (pid2 > 0)
		{
			close(7);
			close(8);
			close(5);
			close(6);
			for (int j = 0; j < 3; ++j)
			{
				if (pid2 == wait(&tmp))
				{
					status = tmp;
				}
			}
		}
		else
		{
			printf("fork error\n");
		}
		if (WIFEXITED(status))
			printf("es: %d\n", WEXITSTATUS(status));
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
	dup2(stdin_dup, STDIN_FILENO);
	dup2(stdout_dup, STDOUT_FILENO);
	close(stdin_dup);
	close(stdout_dup);
}