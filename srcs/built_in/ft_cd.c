#include "minishell.h"

char	*ft_getenv(t_env_node *head, char *key)
{
	head = head->next;
	while (head)
	{
		if (ft_strcmp(key, head->key) == 0)
		{
			if (head->value)
				return (ft_strdup_s(head->value));
			else
				return (NULL);
		}
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
			head->value = ft_strdup_s(value);
			break ;
		}
		head = head->next;
	}
}

static void	cd_with_path(t_env_node *head, char **path, \
							char **old_path, char **argv)
{
	if (chdir(*path) == -1)
	{
		free(*old_path);
		free(*path);
		*old_path = ft_strjoin_s("minishell: cd: ", argv[1]);
		if (access(argv[1], F_OK))
			*path = ft_strjoin_s(*old_path, ": No such file or directory\n");
		else
			*path = ft_strjoin_s(*old_path, ": Not a directory\n");
		ft_putstr_fd(*path, STDERR_FILENO);
		g_exit_status = 1;
	}
	else
	{
		ft_setenv("OLDPWD", *old_path, head);
		ft_setenv("PWD", getcwd(NULL, 0), head);
		g_exit_status = 0;
	}
}

static char	*cd_with_oldpwd(t_env_node *head, char *old_path)
{
	char	*path;

	path = ft_getenv(head, "OLDPWD");
	if (!path)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		free(old_path);
		g_exit_status = 1;
		return (NULL);
	}
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (path);
}

void	ft_cd(t_env_node *head, char **argv)
{
	char	*old_path;
	char	*path;
	char	*tmp;

	old_path = getcwd(NULL, 0);
	if (!argv[1])
		path = ft_getenv(head, "HOME");
	else if (argv[1][0] == '~')
	{
		tmp = ft_getenv(head, "HOME");
		path = ft_strjoin_s(tmp, argv[1] + 1); // TODO malloc 터지면 exit?
		free(tmp);
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		path = cd_with_oldpwd(head, old_path);
		if (!path)
			return ;
	}
	else
		path = ft_strdup_s(argv[1]);
	cd_with_path(head, &path, &old_path, argv);
	free(old_path);
	free(path);
}
