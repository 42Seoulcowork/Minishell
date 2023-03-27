#include "minishell.h"

static char	*ft_getenv(char *key, t_envp *tenvp)
{
	int	i;

	i = -1;
	key = ft_strjoin(key, "=");
	while (tenvp->envp[++i])
	{
		if (ft_strncmp(key, tenvp->envp[i], ft_strlen(key)) == 0)
			return (ft_strdup(tenvp->envp[i] + ft_strlen(key)));
	}
	return (NULL);
}

static int	ft_setenv(char *key, char *value, t_envp *tenvp)
{
	int	i;
	int	flag;

	i = -1;
	flag = 1;
	key = ft_strjoin(key, "=");
	while (tenvp->envp[++i])
	{
		if (ft_strncmp(key, tenvp->envp[i], ft_strlen(key)) == 0)
		{
			tenvp->envp[i] = ft_strjoin(key, value);
			flag = 0;
			break ;
		}
	}
	free(value);
	if (flag)
		return (-1);
	return (0);
}

void	ft_cd(char **argv, t_envp *tenvp)
{
	int		flag;
	char	*path;

	flag = 0;
	flag += ft_setenv("OLDPWD", getcwd(NULL, 0), tenvp);
	if (!argv[1])
		path = ft_getenv("HOME", tenvp); // TODO error 처리해야 함
	else if (argv[1][0] == '~')
		path = ft_strjoin(ft_getenv("HOME", tenvp), argv[1] + 1); // TODO error 처리해야 함
	else
		path = argv[1];
	flag += chdir(path);
	flag += ft_setenv("PWD", getcwd(NULL, 0), tenvp);
	if (flag)
	{
		path = ft_strjoin(ft_strjoin("minishell: cd: ", path), ": No such file or directory\n");
		ft_putstr_fd(path, STDERR_FILENO);
	}
}
