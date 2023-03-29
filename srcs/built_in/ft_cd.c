#include "minishell.h"

static char	*ft_getenv(char *key, t_env_node *head)
{
	head = head->next;
	while (head)
	{
		if (ft_strcmp(key, head->key) == 0)
			return (ft_strdup(head->key));
		head = head->next;
	}
	return (NULL);
}

static int	ft_setenv(char *key, char *value, t_env_node *head)
{
	int	flag;

	flag = -1;
	head = head->next;
	while (head != NULL)
	{
		if (ft_strcmp(key, head->key) == 0)
		{
			head->value = ft_strdup(value);
			flag = 0;
			break ;
		}
		head = head->next;
	}
	free(value);
	return (flag);
}

void	ft_cd(char **argv, t_env_node *head)
{
	int		flag;
	char	*path;

	flag = 0;
	flag += ft_setenv("OLDPWD", getcwd(NULL, 0), head);
	if (!argv[1])
		path = ft_getenv("HOME", head); // TODO error 처리해야 함
	else if (argv[1][0] == '~')
		path = ft_strjoin(ft_getenv("HOME", head), argv[1] + 1); // TODO error 처리해야 함
	else
		path = argv[1];
	flag += chdir(path);
	flag += ft_setenv("PWD", getcwd(NULL, 0), head);
	if (flag)
	{
		path = ft_strjoin(ft_strjoin("minishell: cd: ", path), ": No such file or directory\n");
		ft_putstr_fd(path, STDERR_FILENO);
	}
}
