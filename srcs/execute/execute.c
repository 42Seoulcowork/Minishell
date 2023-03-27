#include "minishell.h"

void	execute(t_token *tokens, t_envp *tenvp)
{
	char 	*str;

	str = "temp";
	(void)tokens;
	if (ft_strcmp(str, "echo $?") == 0)
	{
		printf("%d\n", tenvp->exit_status);
		tenvp->exit_status = 0;
	}
	else if (ft_strchr(str, '|'))
		pipex(str, tenvp);
	else if (ft_strncmp(str, "echo ", 5) == 0)
		ft_echo(ft_split(str, ' ')); // TODO 토큰을 사용하도록 변경해야 함
	else if (ft_strcmp(str, "pwd") == 0) // TODO 토큰을 사용하도록 변경해야 함
		ft_pwd();
	else if (ft_strncmp(str, "exit ", 5) == 0 || ft_strcmp(str, "exit") == 0)
		ft_exit(ft_split(str, ' ')); // TODO 토큰을 사용하도록 변경해야 함
	else if (ft_strcmp(str, "env") == 0)
		ft_env(tenvp->envp);
	else
		run_cmd(str, tenvp);
}