#include "minishell.h"

static int	check_echo_option(char **args)
{
	int i;

	i = 0;
	if (args[1][0] == '-' && args[1][1] == 'n')
	{
		i = 1;
		while (args[1][i] == 'n')// '-nnnnn'과 같은 케이스 처리
			i++;
		if (args[1][i] != '\0')// '-nnnnx'와 같은 케이스 처리
			return (0);
	}
	return (i);
}

void	ft_echo(char **args)// args는 node.cmdline.cmd
{
	int	i;// int? or size_t?
	int	j;
	int	option_flag;

	if (!args[1])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	option_flag = check_echo_option(args);
	i = (option_flag > 0) ? 1 : 0;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
			write(1, &args[i][j], 1);
		if (args[i + 1])
			write(1, " ", 1);
	}
	if (!option_flag)
		write(1, "\n", 1);
}
