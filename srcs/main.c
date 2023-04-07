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
//		parsing(str, &parsed_data, head);
		parsed_data.front = malloc(sizeof(t_token));
		parsed_data.pipe_cnt = 0;
		parsed_data.front->cmd = ft_split(str, ' ');
		if (ft_strncmp("cd", str, 2) == 0)
			parsed_data.front->cmd_type = CD_FUNC;
		else if (ft_strncmp("echo", str, 4) == 0)
			parsed_data.front->cmd_type = ECHO_FUNC;
		else if (ft_strncmp("env", str, 3) == 0)
			parsed_data.front->cmd_type = ENV_FUNC;
		else if (ft_strncmp("exit", str, 4) == 0)
			parsed_data.front->cmd_type = EXIT_FUNC;
		else if (ft_strncmp("export", str, 6) == 0)
			parsed_data.front->cmd_type = EXPORT_FUNC;
		else if (ft_strncmp("unset", str, 5) == 0)
			parsed_data.front->cmd_type = UNSET_FUNC;
		else if (ft_strncmp("pwd", str, 3) == 0)
			parsed_data.front->cmd_type = PWD_FUNC;
		else
			parsed_data.front->cmd_type = EXTERN_FUNC;
		parsed_data.front->redir = NULL;
		parsed_data.front->next = NULL;
		execute(head, &parsed_data);
		if (str[0] != '\0')
			add_history(str);
		printf("exit_status: %d\n", g_exit_status);
		free(str);
	}
	return (0);
}
