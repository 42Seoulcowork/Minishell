#include "minishell.h"

static char	*find_path(char *cmd, char **path)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin_s(path[i], "/");
		free(path[i]);
		path[i] = ft_strjoin_s(tmp, cmd);
		free(tmp);
		if (access(path[i], F_OK) == 0)
			return (ft_strdup_s(path[i]));
		++i;
	}
	if (access(cmd, F_OK) == 0 && cmd[0] == '/')
		return (cmd);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (NULL);
}

char	*check_path(t_env_node *head, t_token *token)
{
	char	*tmp;
	char	*path;
	char	**env_path;

	if (token->cmd[0][0] == '.' && token->cmd[0][1] == '/')
	{
		if (access(*(token->cmd) + 2, F_OK) == -1)
			handle_null_path(token->cmd[0]);
		path = token->cmd[0];
	}
	else if (token->cmd[0][0] == '/')
	{
		if (access(*(token->cmd), F_OK) == -1)
			handle_null_path(token->cmd[0]);
		path = token->cmd[0];
	}
	else
	{
		tmp = ft_getenv(head, "PATH");
		if (tmp == NULL)
			handle_null_path(token->cmd[0]);
		env_path = ft_split_s(tmp, ':');
		free(tmp);
		path = find_path(token->cmd[0], env_path);
		free_env_path(env_path);
		if (!path)
			exit(127);
	}
	return (path);
}

static void	is_directory(char *path, char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir == NULL)
		return ;
	print_is_directory(path, cmd);
	closedir(dir);
}

void	run_cmd(t_env_node *head, t_token *token)
{
	char	*path;

	path = check_path(head, token);
	if (access(path, X_OK) != 0)
		print_permission_denied(path, token->cmd[0]);
	is_directory(path, token->cmd[0]);
	if (execve(path, token->cmd, convert_array_for_execve(head)) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(token->cmd[0]);
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(1);
	}
}
