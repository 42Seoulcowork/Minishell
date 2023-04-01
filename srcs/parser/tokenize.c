#include "../../includes/minishell.h"

void	ft_tokenize(char *input, t_p_data *pdata, t_word *word, t_env_node *head)
{
	if (word->dq_stt == OFF && word->sq_stt == OFF && *input == '\n')
		ft_end_line_finish_hpwtt(pdata, word);
	else if (word->dq_stt == OFF && word->sq_stt == OFF && *input == '|')
		ft_add_new_token_hpwtt(pdata, word);
	else if ((word->sq_stt == ON && *input == '\'') || \
		(word->dq_stt == ON && *input == '\"'))
		ft_end_quoted_stt(*input, word);
	else if ((word->sq_stt == OFF && *input == '\'') || \
		(word->dq_stt == OFF && *input == '\"'))
		ft_start_quoted_stt(*input, word);
	else if (word->sq_stt == OFF && *input == '$')
		ft_expension_process(&input, word, head);
	else if (word->dq_stt == OFF && word->sq_stt == OFF && \
		(*input == '<' || *input == '>'))
		ft_redirect_hpwtt(&input, pdata);
	else if (word->dq_stt == OFF && word->sq_stt == OFF && *input == ' ')
		ft_clean_new_word_hpwtt(pdata, word);
	else if (*input == '#' && word->word[0] == '\0' && \
		word->dq_stt == OFF && word->sq_stt == OFF)
		ft_handle_comment(word);
	else
		ft_add_or_create_new_char_in_word(word);
}
