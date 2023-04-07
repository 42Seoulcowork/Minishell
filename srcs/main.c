#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_p_data	parsed_data;
	t_env_node	*head;

	head = init_node(envp);
	if (ac != 1)
		return (0);
	if (!ft_strcmp(av[0], "minishell"))
		return (0);
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
		if (parsed_data.front->cmd != NULL)
		{
			execute(head, &parsed_data);
			if (str[0] != '\0')
				add_history(str);
			printf("exit_status: %d\n", g_exit_status);
		}
		free(str);
	}
	return (0);
}
