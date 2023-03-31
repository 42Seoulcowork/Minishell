#include "minishell.h"

static char	*find_path(char *cmd, char **path)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path[i], F_OK) == 0)
			return (ft_strdup(path[i]));
		++i;
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	// exit status 127
	return (NULL);
}

static void	print_permission_denied(char *path, char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	free(path);
}

static void	free_env_path(char **env_path)
{
	int	i;

	i = 0;
	while (env_path[i] != NULL)
	{
		free(env_path[i]);
		++i;
	}
	free(env_path);
}

void	handle_redir(t_redir *redir)
{
	int fd;

	while (redir != NULL)
	{
		if (redir->type == RE_INPUT)
		{
			fd = open(redir->file_name, O_RDONLY);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->file_name, STDERR_FILENO);
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
				return ;
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == RE_OUTPUT)
		{
			fd = open(redir->file_name, O_CREAT, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == RE_APPEND)
		{
			fd = open(redir->file_name, O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
}

void	run_cmd(t_token *token, t_env_node *head)
{
	int 	status;
	char	*tmp;
	char	*path;
	char 	**env_path;
	pid_t	pid;

	token = malloc(sizeof(t_token));
	token->cmd = ft_split("cat", ' ');
	token->redir = malloc(sizeof(t_redir));
	token->redir->type = RE_INPUT;
	token->redir->file_name[0] = 'z';
	token->redir->file_name[1] = '\0';
	token->redir->next = NULL;

	if (token->redir != NULL)
	{
		handle_redir(token->redir);
	}
	if (token->cmd[0][0] == '.' && token->cmd[0][1] == '/')
	{
		path = token->cmd[0];
	}
	else
	{
		tmp = ft_getenv("PATH", head);
		env_path = ft_split(tmp, ':');
		free(tmp);
		path = find_path(token->cmd[0], env_path);
		free_env_path(env_path);
		if (!path)
			return;
	}
	if (access(path, X_OK) != 0)
		return (print_permission_denied(path, token->cmd[0]));
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, token->cmd, convert_array_for_execve(head)) == -1)
		{
			perror("minishell: ");
			ft_putstr_fd("\n", STDERR_FILENO);
		}
	}
	else if (pid > 0)
	{
		wait(&status);
		printf("status = %d\n", status);
		// 종료상태 반환, 저장만
	}
	else
	{
		perror("minishell: ");
		ft_putstr_fd("\n", STDERR_FILENO);
		// fork error
	}
	if (WIFEXITED(status))
		printf("status = %d\n", WEXITSTATUS(status));
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
