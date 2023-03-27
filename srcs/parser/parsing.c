#include "minishell.h"

t_parsed_data	*parsing(char *str)
{
	t_parsed_data	*ret;

	ret = (t_parsed_data *)malloc(sizeof(t_parsed_data));
	*ret = tokenize(str);
	return (ret);
}
