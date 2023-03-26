#include "minishell.h"

char	*ft_pwd(void)
{
	return (getcwd(NULL, 0));
}
