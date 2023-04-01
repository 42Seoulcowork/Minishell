#include "../../includes/minishell.h"

void	ft_tokenize(char *input, t_p_data *pdata, t_word *word)
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
		ft_expension_process(&input, word);
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


// size_t	ft_strnlen(const char *s, size_t maxlen)
// {
// 	size_t	len;

// 	len = 0;
// 	while (len < maxlen && s[len] != '\0')
// 		len++;
// 	return (len);
// }

// char	*ft_strndup(const char *s, size_t n)
// {
// 	size_t	len;
// 	char	*dup;

// 	len = ft_strnlen(s, n);
// 	dup = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!dup)
// 		return (NULL);
// 	dup[len] = '\0';
// 	return (ft_memcpy(dup, s, len));
// }
