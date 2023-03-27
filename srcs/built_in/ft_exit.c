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
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
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

void	ft_exit(char **args)
{
	int		exit_status;
	char 	*msg;

	printf("exit\n");
	if (!args[1])
	{
		exit_status = 0;
		exit(0);
	}
	else if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		// 종료 상태 1로 변경
		return ;
	}
	exit_status = ft_atouc(args[1]);
	if (exit_status == -1)
	{
		msg = ft_strjoin(ft_strjoin("minishell: exit: ", args[1]), ": numeric argument required\n");
		ft_putstr_fd(msg, STDERR_FILENO);
		exit_status = 2;
	}
	printf("exit status: %d\n", exit_status); // TODO 현재 종료 상태 확인, 출력이 아니라 종료 상태에 저장되도록 변경해야 함
	exit(exit_status);
}
