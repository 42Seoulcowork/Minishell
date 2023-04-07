#include "minishell.h"

void	ft_handle_comment(t_word *word)
{
	word->break_flag = ON;
}

void	ft_clean_new_word_hpwtt(t_p_data *pdata, t_word *word, t_env_node *node)
{
	if (word->ex_stt == ON)
		ft_expension_process(word, node);
	if (word->re_stt == ON)
	{
		if (ft_strcmp(word->word + word->re_idx, ">")
			|| ft_strcmp(word->word + word->re_idx, "<")
			|| ft_strcmp(word->word + word->re_idx, ">>")
			|| ft_strcmp(word->word + word->re_idx, "<<"))
			return ;
		ft_redirection_process(pdata, word);
	}
	ft_handle_present_w_cmd_to_token(pdata, word);
	if (pdata->now->cmd == NULL && pdata->now->redir == NULL \
		&& word->ex_idx == -1)
		ft_syntax_error();
	ft_clear_word_struct(word);
}

void	ft_add_or_start_new_char_in_word(char input, t_word *word)
{
	word->word[++(word->word_idx)] = input;
}
