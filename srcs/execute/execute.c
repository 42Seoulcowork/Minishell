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

void		execute_token(t_env_node *head, t_token *token)
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

void	execute(t_env_node *head, t_p_data *p_data)
{
	int	stdin_dup;
	int	stdout_dup;
	int **fd;
	int i;
	int	tmp;
	int status;
	pid_t pid;

	stdin_dup = dup(STDIN_FILENO);
	stdout_dup = dup(STDOUT_FILENO);
	i = 0;
	pid = 0;
	if (p_data->pipe_cnt == 0)
	{
		if (p_data->front->cmd_type == EXTERN_FUNC)
			pid = fork();
		if (pid > 0)
			wait(&status);
		else if (pid == 0)
			execute_token(head, p_data->front);
		else
			perror("fork");
	}
	else
	{
		fd = malloc(sizeof(int *) * p_data->pipe_cnt);
		while (i < p_data->pipe_cnt)
		{
			fd[i] = malloc(sizeof(int) * 2);
			++i;
		}
		if (pipe(fd[0]) == -1)
		{
			g_exit_status = 1;
			// error 처리
		}
		pid = fork();
		if (pid == 0)
		{
			close(fd[0][READ_END]);
			dup2(fd[0][WRITE_END], STDOUT_FILENO);
			close(fd[0][WRITE_END]);
			execute_token(head, p_data->front);
		}
		else if (pid > 0)
		{
			close(fd[0][WRITE_END]);
			p_data->front = p_data->front->next;
		}
		else
		{
			g_exit_status = 1;
			printf("fork error\n");
		}
		i = 0;
		while (i < p_data->pipe_cnt - 1)
		{
			++i;
			pipe(fd[i]);//todo pipe error
			pid = fork();
			if (pid == 0) // 자식
			{
				close(fd[i][READ_END]);
				dup2(fd[i - 1][READ_END], STDIN_FILENO);
				close(fd[i - 1][READ_END]);
				dup2(fd[i][WRITE_END], STDOUT_FILENO);
				close(fd[i][WRITE_END]);
				execute_token(head, p_data->front);
			}
			else if (pid > 0)
			{
				close(fd[i - 1][READ_END]);
				close(fd[i][WRITE_END]);
				p_data->front = p_data->front->next;
			}
			else
			{
				g_exit_status = 1;
				// error
			}
		}
		pid = fork();
		if (pid == 0) // 자식
		{
			dup2(fd[i][READ_END], STDIN_FILENO);
			close(fd[i][READ_END]);
			execute_token(head, p_data->front);
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
		}
		else
		{
			g_exit_status = 1;
			printf("fork error\n");
		}
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
	dup2(stdin_dup, STDIN_FILENO);
	dup2(stdout_dup, STDOUT_FILENO);
	close(stdin_dup);
	close(stdout_dup);
}