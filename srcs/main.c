#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*str;
	char	*cwd;
	char	**path;

	(void)envp;
	if (ac != 1)
		return (0);
	if (!ft_strcmp(av[0], "minishell"))
		return (0);
	path = ft_split(getenv("PATH"), ':');
	while (1)
	{
		str = readline("$>");
		if (!str)
			break ;
		printf("%s\n", str);
		cwd = getcwd(NULL, 1);
		if (cwd)
			printf("%s\n", cwd);
		add_history(str);
		free(str);
	}
	return (0);
}
