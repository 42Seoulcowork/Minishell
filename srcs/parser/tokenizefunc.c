#include "../../includes/minishell.h"

void	ft_clear_word_struct(t_word *word)
{
	word->dq_stt = OFF;
	word->sq_stt = OFF;
	word->type = COMMAND;
	word->break_flag = OFF;
	ft_memset(word, '\0', ARG_MAX);
}

void	ft_handle_present_word_to_token(t_p_data *pdata, t_word *word)
{
	t_redir	*present_redir;
	t_redir	*temp;

	if (word->type == COMMAND)
		ft_append_cmd_to_token(pdata, word);
	else
	{
		present_redir = (t_redir *)malloc(sizeof(t_redir));
		if (!present_redir)
			ft_allocation_error();
		present_redir->next = NULL;
		temp = pdata->now->redir;
		if (!temp)
			pdata->now->redir = present_redir;
		else
		{
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = present_redir;
		}
		present_redir->type = word->type;
		ft_strlcpy(present_redir->file_name, word->word, PATH_MAX);
	}
}
/* here-doc should make un-named file & save path in word[ARG_MAX] */
/* word->type == RE_TYPE : create_redic_struct , present_redic_word_to_token */
