#include "minishell.h"

int	main(void)
{
	char	*str;
	char	*cwd;
	char	**path;

	// ft_basic_signal();
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
