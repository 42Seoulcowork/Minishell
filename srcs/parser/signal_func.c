#include "minishell.h"

void	signal_handler(int sig)
{
	g_exit_status += sig;
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		exit (1);
	}
}

void	signal_handler_2(int sig)
{
	g_exit_status += sig;
	if (sig == 2)
	{
		g_exit_status = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signal_init(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
