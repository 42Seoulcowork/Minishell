#include "minishell.h"

void	ft_allocation_error(void)
{
	write(2, "Allocation Error!\n", 18);
}

void	ft_pipe_syntax_error(void)
{
	write(2, "pipe_syntax Error!\n", 19);
}

void	ft_stx_near_unexp_tk_error(void)
{
	write(2, "bash: parse error near \n", 24);
}

void	ft_ambiguous_redirect_error(void)
{
	write(2, "Ambiguous Redirect Error!\n", 26);
}
