#include "../../includes/minishell.h"

void	ft_end_line_finish_hpwtt(t_p_data *pdata, t_word *word)
{
	ft_handle_present_word_to_token(pdata, word);
	ft_clear_word_struct(word);
	word->break_flag = ON;
}

void	ft_add_new_token_hpwtt(t_p_data *pdata, t_word *word)
{
	t_token	*new_token;	

	ft_handle_present_word_to_token(pdata, word);
	ft_clear_word_struct(word);
	if (pdata->now->cmd == NULL && pdata->now->redir == NULL)
		ft_pipe_syntax_error();
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		ft_allocation_error();
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


// int	ft_strlen_for_exp(const char *s, )
// {
// 	const char	*copy;

// 	if (!s)
// 		return (0);
// 	copy = s;
// 	while (!(*s == ' ' || *s == '|' || *s == '\n' || *s == 0))
// 		s++;
// 	return ();
// }

void	ft_expension_process(char **input, t_word *word)
{
	char	*tmp;

	if (*(*input + 1) == ' ' || *(*input + 1) == '|' || *(*input + 1) == '\n')
		word->word[++(word->word_idx)] = '$';
	// else
	// 	tmp = ft_make_st()
}
