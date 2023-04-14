#include "minishell.h"

void	signal_handler_for_parrent(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 1;
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

void	signal_handler(int sig)
{
	char	*tmp;

	if (sig == SIGINT)
	{
		g_exit_status = 1; // TODO 빈 프롬프트에 SIGINT를 넣으면 종료상태가 1로 변함, bash가
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line(); // TODO 자식 기다릴 떄, 이 동작 있으면 안 됨
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		tmp = ft_itoa(g_exit_status);
		if (!tmp)
			ft_allocation_error();
		ft_putstr_fd("Quit: ", STDERR_FILENO);
		ft_putstr_fd(tmp, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
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
