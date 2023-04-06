#include "minishell.h"

void	ft_handle_comment(t_word *word)
{
	word->break_flag = ON;
}

void	ft_add_new_word(t_p_data *pdata, t_word *word, t_env_node *head)
{
	if (word->re_stt == ON)
	{
		if (pdata->now->redir == NULL)
		{
			pdata->now->redir = (t_redir *)malloc(sizeof(t_redir));
			if (pdata->now->redir == NULL)
				ft_allocation_error();
			ft_bzero(pdata->now->redir, sizeof(t_redir));
		}
		if (word->type == RE_INPUT)
			pdata->now->redir->type = RE_INPUT;
		else if (word->type == RE_OUTPUT)
			pdata->now->redir->type = RE_OUTPUT;
		else if (word->type == RE_APPEND)
			pdata->now->redir->type = RE_APPEND;
		else if (word->type == RE_HERE)
			pdata->now->redir->type = RE_HERE;
		ft_strlcpy(pdata->now->redir->file_name, word->word, PATH_MAX);
	}
	else
		ft_handle_present_word_to_token(pdata, word);
}

void	ft_clean_new_word_hpwtt(t_p_data *pdata, t_word *word, t_env_node *head)
{
	if (word->word_idx > 0)
	{
		word->word[word->word_idx] = '\0';
		ft_add_new_word(pdata, word, head);
	}
	word->dq_stt = OFF;
	word->sq_stt = OFF;
	word->ex_stt = OFF;
	word->re_stt = OFF;
	word->word_idx = 0;
}



// void	ft_add_or_create_new_char_in_word(t_word *word)
// {

// }
