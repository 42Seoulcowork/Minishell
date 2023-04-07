#include "minishell.h"

void	ft_syntax_error(void)
{
	write(2, "syntax Error!\n", 14);
}

void	ft_stx_near_unexp_tk_error(void)
{
	write(2, "bash: parse error near \n", 24);
}

void	ft_ambiguous_redirect_error(void)
{
	write(2, "Ambiguous Redirect Error!\n", 26);
}
