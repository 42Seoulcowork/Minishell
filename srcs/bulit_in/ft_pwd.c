#include "minishell.h"

void	ft_pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	if (path)
	{
		path = ft_strjoin(path, "\n");
		ft_putstr_fd(path, STDOUT_FILENO);
		// 종료 상태 0;
	}
	else
	{
		ft_putstr_fd("minishell: pwd: no path\n", STDERR_FILENO); // 에러 메세지는 임의로 작성함
		// errno에 맞춘 에러 생성;
	}
}
