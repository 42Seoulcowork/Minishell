#include "minishell.h"

void	ft_here_doc_acting(t_redir *new, char *tmp)
{
	char	*str;
	pid_t	pid;
	int		status;

	if (g_exit_status == HERE_DOC_SIGINT)
		return ;
	rl_catch_signals = 1;
	pid = fork_s();
	if (pid == 0)
	{
		ft_signal_child();
		while (1)
		{
			str = readline("> ");
			if (!str || ft_strcmp(tmp, str) == 0)
			{
				if (str)
					free_s(str);
				exit(0);
			}
			write(new->heredoc_fd, str, ft_strlen(str));
			write(new->heredoc_fd, "\n", 1);
			free_s(str);
		}
	}
	signal(SIGINT, signal_handler_for_parent);
	wait(&status);
	if (WIFSIGNALED(status))
	{
		printf("\n");
		g_exit_status = HERE_DOC_SIGINT;
	}
}
