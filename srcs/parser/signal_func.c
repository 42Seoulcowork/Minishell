#include "minishell.h"

void	signal_handler(int sig)
{
	char	*tmp;

	if (sig == SIGINT)
	{
		g_exit_status = 1; // TODO 빈 프롬프트에 SIGINT를 넣으면 종료상태가 1로 변함, bash가
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		tmp = ft_itoa(g_exit_status);
		if (!tmp)
			ft_allocation_error();
		write(STDERR_FILENO, "Quit: ", 6);
		write(STDERR_FILENO, tmp, ft_strlen(tmp));
		write(STDERR_FILENO, "\n", 1);
		free_s(tmp);
		exit(1);
	}
}

void	ft_signal_init(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, signal_handler);
}
