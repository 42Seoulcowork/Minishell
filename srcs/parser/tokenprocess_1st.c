#include "../../includes/minishell.h"

void	ft_end_line_finish_hpwtt(t_p_data *pdata, t_word *word)
{
	ft_handle_present_word_to_token(pdata, word);
	ft_clear_word_struct(word);
	word->break_flag = ON;
}
