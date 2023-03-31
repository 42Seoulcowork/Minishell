#include "minishell.h"

static int	overflow_up_check(long long result, char num)
{
	if (result == 922337203685477580 && num > '7')
		return (0);
	if (result > 922337203685477580)
		return (0);
	return (1);
}

static int	overflow_down_check(long long result, char num)
{
	if (result == -922337203685477580 && num > '8')
		return (0);
	if (result < -922337203685477580)
		return (0);
	return (1);
}

static int	ft_atouc(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (!overflow_up_check(result, str[i]))
			return (-1);
		if (!overflow_down_check(result, str[i]))
			return (-1);
		result = result * 10 + (str[i] - '0') * sign;
		i++;
	}
	if (str[i])
		return (-1);
	return ((unsigned char)result);
}

void	ft_exit(t_env_node *head, char **args)
{
	int		exit_status;
	char 	*msg;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!args[1])
	{
		exit(ft_atoi(head->value));
	}
	exit_status = ft_atouc(args[1]);
	if (exit_status == -1)
	{
		msg = ft_strjoin(ft_strjoin("minishell: exit: ", args[1]), ": numeric argument required\n");
		ft_putstr_fd(msg, STDERR_FILENO);
		exit_status = 255;
	}
	else if (args[2]) // args[1]을 먼저 확인
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		head->value = "1";
		return ;
	}
	exit(exit_status);
}
