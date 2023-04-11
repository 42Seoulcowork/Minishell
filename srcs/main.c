#include "minishell.h"

static t_env_node	*initialize(int ac, char **av, char **envp)
{
	if (ac != 1)
		exit(1);
	if (!ft_strcmp(av[0], "minishell"))
		exit(1);
	return (init_node(envp));
}

int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_p_data	parsed_data;
	t_env_node	*head;

	head = initialize(ac, av, envp);
	//signal_setting();
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		parsing(str, &parsed_data, head->next);
		if (parsed_data.front && (parsed_data.front->cmd || parsed_data.front->redir))
		{
			execute(head, &parsed_data);
			if (str[0] != '\0')
				add_history(str);
		}
		free(str);
	}
	return (0);
}
