#include "minishell.h"

// 우리가 가져오는 건 프로그램이 실행될 당시 쉘의 환경변수

void	ft_env(t_env_node *head)
{
	head->value = "0";
	head = head->next;
	while (head)
	{
		if (head->value)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}
