#include "../../includes/minishell.h"

static void	ft_init_token_word(t_p_data *pdata, t_word *word)
{
	pdata->now = pdata->front;
	pdata->pipe_cnt = 0;
	pdata->front->cmd = NULL;
	pdata->front->cmd_type = EXTERN_FUNC;
	pdata->front->redir = NULL;
	pdata->front->next = NULL;
	ft_clear_word_struct(word);
}

void	parsing(char *input, t_p_data *pdata)
{
	t_word	word;

	pdata->front = (t_token *)malloc(sizeof(t_token));
	if (!pdata->front)
		ft_allocation_error();
	ft_init_token_word(pdata, &word);
	while (word.break_flag == OFF && *input)
	{
		ft_tokenize(input, pdata, &word);
		++input;
	}
}
