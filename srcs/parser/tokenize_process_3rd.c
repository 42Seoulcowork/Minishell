#include "minishell.h"

void	ft_redirect_hpwtt(char **input, t_p_data *pdata)
{
	if (*(*input) == '<' && *(*input + 1) == '<')
	{
		if (*(*input + 2) == '<')
			ft_redirect_syntax_error();
		// heredoc
	}
	else if (*(*input) == '<')
	{
		//input
	}
	else if (*(*input) == '>' && *(*input) == '>')
	{
		if (*(*input + 2) == '>')
			ft_redirect_syntax_error();
		//append
	}
	else if (*(*input) == '>')
	{
		//output
	}
}