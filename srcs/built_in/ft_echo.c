#include "minishell.h"

static int	check_echo_option(char **args)
{
	int i;

	i = 0;
	if (args[1][0] == '-' && args[1][1] == 'n')
	{
		i = 1;
		while (args[1][i] == 'n')
			i++;
		if (args[1][i] != '\0')
			return (0);
	}
	return (i);
}

void	ft_echo(char **args)
{
	int	i;
	int	j;
	int	option_flag;

	g_exit_status = 0;
	if (!args[1])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	option_flag = check_echo_option(args);
	i = 0;
	if (option_flag > 0)
		i = 1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
			write(STDOUT_FILENO, &args[i][j], 1);
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!option_flag)
		write(STDOUT_FILENO, "\n", 1);
}
