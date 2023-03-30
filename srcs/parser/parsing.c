#include "minishell.h"

void	parsing(char *str, t_p_data *pdata)
{
	pdata = (t_p_data *)malloc(sizeof(t_p_data));
	*pdata = tokenize(str);
}
