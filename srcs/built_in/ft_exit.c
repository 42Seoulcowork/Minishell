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

void	ft_exit(char **args, int child)
{
	int		input_status;
	char	*msg;
	char	*tmp;

	if (child == FALSE)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!args[1])
		exit(g_exit_status);
	input_status = ft_atouc(args[1]);
	if (input_status == -1)
	{
		tmp = ft_strjoin_s("minishell: exit: ", args[1]);
		msg = ft_strjoin_s(tmp, ": numeric argument required\n");
		free(tmp);
		ft_putstr_fd(msg, STDERR_FILENO);
		g_exit_status = 255;
	}
	else if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_exit_status = 1;
		return ;
	}
	g_exit_status = input_status; // TODO 바꿈 이래도 자식에서 실행되면 안 바뀌는데 모르겟다
	exit(g_exit_status);
}
