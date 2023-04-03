#include "minishell.h"

void	ft_el_fin_hpwtt(t_p_data *pdata, t_word *word, t_env_node *node)
{
	if (word->ex_stt == ON)
		ft_expension_process(word, node);
	ft_handle_present_word_to_token(pdata, word);
	if (pdata->now->cmd == NULL && pdata->now->redir == NULL \
		&& word->ex_idx == -1)
		ft_pipe_syntax_error();
	ft_clear_word_struct(word);
	word->break_flag = ON;
}

void	ft_add_new_token_hpwtt(t_p_data *pdata, t_word *word, t_env_node *node)
{
	t_token	*new_token;	

	if (word->ex_stt == ON)
		ft_expension_process(word, node);
	if (word->re_stt == ON)
		ft_redirection_process(pdata, word);
	ft_handle_present_word_to_token(pdata, word);
	if (pdata->now->cmd == NULL && pdata->now->redir == NULL \
		&& word->ex_idx == -1)
		ft_pipe_syntax_error();
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		ft_allocation_error();
	ft_clear_word_struct(word);
	new_token->cmd = NULL;
	new_token->cmd_type = EXTERN_FUNC;
	new_token->redir = NULL;
	new_token->next = NULL;
	pdata->now->next = new_token;
	pdata->now = new_token;
	pdata->pipe_cnt += 1;
}

void	ft_end_quoted_stt(char input, t_word *word)
{
	if (input == '\'')
		word->sq_stt = OFF;
	else if (input == '\"')
		word->dq_stt = OFF;
}

void	ft_start_quoted_stt(char input, t_word *word)
{
	if (input == '\'')
		word->sq_stt = ON;
	else if (input == '\"')
		word->dq_stt = ON;
}

char	*ft_strlen_for_exp(char **input)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while ((*input)[i] != ' ' && (*input)[i] != '|' && \
			(*input)[i] != '\n' && (*input)[i] != '\0')
		i++;
	temp = (char *)malloc(sizeof(char) * (i + 1));
	if (!temp)
		ft_allocation_error();
	j = -1;
	while (++j < i)
		temp[j] = (*input)[j];
	temp[j] = '\0';
	(*input) += i - 1;
	return (temp);
}
