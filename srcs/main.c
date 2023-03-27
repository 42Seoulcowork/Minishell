#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_envp	tenvp;
	t_token	*tokens;

	// ft_basic_signal();
	if (ac != 1)
		return (0);
	if (!ft_strcmp(av[0], "minishell"))
		return (0);
	envp_init(&tenvp, envp);
	//signal_setting();
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		tokens = tokenize(str);
		if (tokens == NULL)
			printf("No tokens");
		print_tokens(tokens);
		if (ft_strcmp(str, "echo $?") == 0)
		{
			printf("%d\n", tenvp.exit_status);
			tenvp.exit_status = 0;
		}
		else if (ft_strchr(str, '|'))
			pipex(str, &tenvp);
		else
			run_cmd(str, &tenvp);
		if (str[0] != '\0')
			add_history(str);
		free(str);
	}
	return (0);
}
