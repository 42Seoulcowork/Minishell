#include "minishell.h"

/*
	TODO
	status에
	1. 문자가 있는지
	2. long long을 벗어나는지 확인

	현재 주영이 ft_atoi.c는 long long에 대한 처리가 없음
* /

void	ft_exit(char *status)
{
	unsigned char	exit_status;

	if (!status)
		exit_status = 0;
//	else if (인자가 두 개이면)
//	{
//		종료상태는 1;
//		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
//	}
	else
		exit_status = 1;
	printf("exit\n");
	exit(exit_status);
}