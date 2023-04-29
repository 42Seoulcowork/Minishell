#include "minishell.h"

static int	check_echo_option(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-' && arg[1] == 'n')
	{
		i = 1;
		while (arg[i] == 'n')
			i++;
		if (arg[i] != '\0')
			return (0);
	}
	return (i);
}

static int	loop_echo(char **args, char *str, int *newline_flag, int no_option)
{
	int	i;
	int	j;
	int	str_index;
	int	option_flag;

	i = 0;
	str_index = -1;
	while (args[++i])
	{
		if (no_option == 0)
			option_flag = check_echo_option(args[i]);
		if (option_flag == 0)
		{
			j = -1;
			while (args[i][++j])
				str[++str_index] = args[i][j];
			if (args[i + 1])
				str[++str_index] = ' ';
			no_option = 1;
		}
		else
			*newline_flag = 0;
	}
	return (str_index);
}

static void	print_args(char **args, int *newline_flag)
{
	int		i;
	int		j;
	int		str_index;
	size_t	count;
	char	*str;

	i = 0;
	j = -1;
	count = 1;
	while (args[++i])
		count += ft_strlen(args[i]) + 1;
	str = malloc_s(count);
	i = -1;
	while (str[++i])
		str[i] = '\0';
	*newline_flag = 1;
	str_index = loop_echo(args, str, newline_flag, 0);
	if (*newline_flag == 1)
		str[++str_index] = '\n';
	write(STDOUT_FILENO, str, ft_strlen(str));
	free_s(str);
}

void	ft_echo(char **args)
{
	int	newline_flag;

	g_exit_status = 0;
	if (!args[1])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	print_args(args, &newline_flag);
}
