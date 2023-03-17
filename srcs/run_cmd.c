#include "minishell.h"

void	run_cmd(char *cmd, t_envp tenvp)
{
	char	*path;
	char	**new_argv;

	tenvp.argc = 1;
	tenvp.argv = malloc(sizeof(char *) * 2);
	if (!tenvp.argv)
		exit(1); // TODO 나중에 에러 처리 잘 해주세요
	tenvp.argv[0] = cmd;
	tenvp.argv[1] = NULL;
	new_argv = argv_init(0, tenvp);
	if (!new_argv)
		error(MALLOC_ERROR, "malloc");
	path = ft_path(new_argv[0], tenvp.paths);
	if (!path)
		error(COMMAND_ERROR, new_argv[0]);
	if (execve(path, new_argv, tenvp.envp) == -1)
		error(RUN_ERROR, new_argv[0]);
}
