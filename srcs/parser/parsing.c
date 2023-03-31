#include "minishell.h"

static void	ft_init_token_word(t_p_data *pdata, t_word *word)
{
	pdata->rear = pdata->front;
	pdata->pipe_cnt = 0;
	pdata->front->cmd = NULL;
	pdata->front->cmd_type = EXTERN_FUNC;
	pdata->front->redir = NULL;
	pdata->front->next = NULL;
	word->dq_state = OFF;
	word->sq_state = OFF;
	word->type = NONE;
	word->break_flag = OFF;
	ft_memset(word, '\0', ARG_MAX);
}

void	parsing(char *input, t_p_data *pdata)
{
	t_word	word;

	pdata->front = (t_token *)malloc(sizeof(t_token));
	if (!pdata->front)
		ft_parcing_error(NULL);
	ft_init_token_word(pdata, &word);
	ft_tokenize(input, pdata, &word);
}
