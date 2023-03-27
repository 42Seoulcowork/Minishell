#include "minishell.h"

// 우리가 가져오는 건 프로그램이 실행될 당시 쉘의 환경변수

void	ft_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}
