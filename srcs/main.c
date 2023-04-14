#include "minishell.h"

static t_env_node	*initialize(int ac, char **av, char **envp)
{
	if (ac != 1)
		exit(1);
	if (!ft_strcmp(av[0], "minishell"))
		exit(1);
	return (init_node(envp));
}

int	ft_print_exit_free_env_all(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

void	free_parsed_data(t_token *front)
{
	int	i;
	t_token *tmp_front;
	t_redir	*tmp_redir;

	while (front)
	{
		i = 0;
		while (front->cmd && front->cmd[i])
		{
			free_s(front->cmd[i]);
			++i;
		}
		free_s(front->cmd);
		while (front->redir)
		{
			tmp_redir = front->redir;
			front->redir = front->redir->next;
			free_s(tmp_redir);
		}
		tmp_front = front;
		front = front->next;
		free_s(tmp_front);
	}
}

int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_p_data	parsed_data;
	t_env_node	*head;

	head = initialize(ac, av, envp);
	ft_signal_init();
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
			return (ft_print_exit_free_env_all());
		ft_signal_init();
		if (str[0] != '\0')
			add_history(str);
		parsing(str, &parsed_data, head->next);
		if (parsed_data.front && (parsed_data.front->cmd || parsed_data.front->redir))
		{
			execute(head, &parsed_data);
			printf("exit_status: %d\n", g_exit_status);
		}
		free_s(str);
	}
	return (0);
}
