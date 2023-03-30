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

void	run_cmd(t_token *token, t_env_node *head)
{
	int 	status;
	char	*tmp;
	char	*path;
	char 	**env_path;
	pid_t	pid;

	tmp = ft_getenv("PATH", head);
	env_path = ft_split(tmp,  ':');
	free(tmp);
	path = find_path(token->cmd[0], env_path);
	free_env_path(env_path);
	if (!path)
		return ;
	if (access(path, X_OK) != 0)
		return (print_permission_denied(path, token->cmd[0]));
	pid = fork();
	if (pid)
	{
		if (execve(path, token->cmd, convert_array(head)) == -1)
			perror("minishell: ");
	}
	else
	{
		wait(&status);
		// 종료상태 반환, 저장만
	}
}
