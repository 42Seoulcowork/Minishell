
#include "minishell.h"

void	tokenize(char *input, t_p_data *pdata, t_word *word, t_env_node *head)
{
	if (word->dq_stt == OFF && word->sq_stt == OFF && *input == '\n')
		ft_end_line_fin_hpwtt(pdata, word, head);
	else if (word->dq_stt == OFF && word->sq_stt == OFF && *input == '|')
		ft_add_new_token_hpwtt(pdata, word, head);
	else if ((word->sq_stt == ON && *input == '\'')
		|| (word->dq_stt == ON && *input == '\"'))
		ft_end_quoted_stt(*input, word);
	else if ((word->sq_stt == OFF && *input == '\'')
		|| (word->dq_stt == OFF && *input == '\"'))
		ft_start_quoted_stt(*input, word);
	else if (word->sq_stt == OFF && *input == '$')
		ft_start_expansion_stt(&input, word);
	else if (word->dq_stt == OFF && word->sq_stt == OFF && word->re_stt == OFF
		&& (*input == '<' || *input == '>'))
		ft_start_redirect_stt(*input, word);
	else if (word->dq_stt == OFF && word->sq_stt == OFF && *input == ' ')
		ft_clean_new_word_hpwtt(pdata, word, head);
//redirection state일때 혹시 전 글자가 '<' '>'면 무시
	else if (*input == '#' && word->word[0] == '\0'
		&& word->dq_stt == OFF && word->sq_stt == OFF)
		ft_handle_comment(word);
	else
		ft_add_or_start_new_char_in_word(*input, word);
}
