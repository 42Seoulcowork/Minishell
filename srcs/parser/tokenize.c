/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekkang <jaekkang@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:39:08 by jaekkang          #+#    #+#             */
/*   Updated: 2023/04/03 19:30:54 by jaekkang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize(char *input, t_p_data *pdata, t_word *word, t_env_node *head)
{
	if (word->dq_stt == OFF && word->sq_stt == OFF && *input == '\n')
		ft_el_fin_hpwtt(pdata, word, head);
	else if (word->dq_stt == OFF && word->sq_stt == OFF && *input == '|')
		ft_add_new_token_hpwtt(pdata, word, head);
	else if ((word->sq_stt == ON && *input == '\'') || \
		(word->dq_stt == ON && *input == '\"'))
		ft_end_quoted_stt(*input, word);
	else if ((word->sq_stt == OFF && *input == '\'') || \
		(word->dq_stt == OFF && *input == '\"'))
		ft_start_quoted_stt(*input, word);
	else if (word->sq_stt == OFF && *input == '$')
		ft_start_expansion_stt(word, head);
	else if (word->dq_stt == OFF && word->sq_stt == OFF && \
		(*input == '<' || *input == '>'))
		ft_redirect_hpwtt(&input, pdata);
	else if (word->dq_stt == OFF && word->sq_stt == OFF && *input == ' ')
		ft_clean_new_word_hpwtt(pdata, word, head);
	else if (*input == '#' && word->word[0] == '\0' && \
		word->dq_stt == OFF && word->sq_stt == OFF)
		ft_handle_comment(word);
	else
		ft_add_or_create_new_char_in_word(word);
}
