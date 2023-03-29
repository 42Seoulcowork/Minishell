#include "minishell.h"

static char	*ft_getenv(char *key, t_env_node *head)
{
	head = head->next;
	while (head)
	{
		if (ft_strcmp(key, head->key) == 0)
			return (ft_strdup(head->value));
		head = head->next;
	}
	return (NULL);
}

static void	ft_setenv(char *key, char *value, t_env_node *head)
{
	head = head->next;
	while (head != NULL)
	{
		if (ft_strcmp(key, head->key) == 0)
		{
			head->value = ft_strdup(value);
			break ;
		}
		head = head->next;
	}
}

void	ft_cd(char **argv, t_env_node *head)
{
	char	*old_path;
	char	*path;

	old_path = getcwd(NULL, 0);
	if (!argv[1])
		path = ft_getenv("HOME", head); // TODO error 처리해야 함
	else if (argv[1][0] == '~')
		path = ft_strjoin(ft_getenv("HOME", head), argv[1] + 1); // TODO error 처리해야 함
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		path = ft_getenv("OLDPWD", head);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
			free(old_path);
			return ;
		}
		ft_putstr_fd(path, STDOUT_FILENO); // linux bash는 우선 cd -일때 OLDPWD를 뱉음
	}
	else
		path = argv[1];
	if (chdir(path)) // 경로 없을 때
	{
		path = ft_strjoin(ft_strjoin("minishell: cd: ", path), ": No such file or directory\n");
		ft_putstr_fd(path, STDERR_FILENO);
	}
	else // 이동했을 때만 갱신
	{
		ft_setenv("OLDPWD", old_path, head);
		ft_setenv("PWD", getcwd(NULL, 0), head);
	}
	free(old_path);
	free(path);
}
