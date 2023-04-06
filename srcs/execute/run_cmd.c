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
	if (access(cmd, F_OK) == 0)
		return (cmd);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (NULL);
}

static void	print_permission_denied(char *path, char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	free(path);
	exit(126);
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

void	run_cmd(t_env_node *head, t_token *token)
{
	char	*tmp;
	char	*path;
	char 	**env_path;

	if (token->cmd[0][0] == '.' && token->cmd[0][1] == '/')
	{
		path = token->cmd[0];
	}
	else
	{
		tmp = ft_getenv(head, "PATH");
		env_path = ft_split(tmp, ':');
		free(tmp);
		path = find_path(token->cmd[0], env_path);
		free_env_path(env_path);
		if (!path)
			exit(127);
	}
	if (access(path, X_OK) != 0)
		print_permission_denied(path, token->cmd[0]);
	if (execve(path, token->cmd, convert_array_for_execve(head)) == -1)
	{
		perror("minishell: ");
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(1);
	}
}
