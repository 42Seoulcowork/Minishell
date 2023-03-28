#include "minishell.h"

void	parsing(char *str, t_p_data *pdata)
{
	t_p_data	*ret;

	ret = (t_p_data *)malloc(sizeof(t_p_data));
	*ret = tokenize(str);
	return (ret);
}
