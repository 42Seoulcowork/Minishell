#include "minishell.h"

void	ft_start_redirect_stt(char input, t_word *word)
{
	word->re_stt = ON;
	(word->word)[++(word->word_idx)] = input;
	word->re_idx = word->word_idx;
}

void	ft_redirection_process(t_p_data *pdata, t_word *word)
{
	t_redir	*new;
	int		tmp_idx;

	ft_append_new_redirect_struct(pdata);
	new = pdata->now->redir;
	while (new->next)
		new = new->next;
	tmp_idx = word->re_idx;
	if (word->word[word->re_idx] == '<')
	{
		if (word->word[++(word->re_idx)] == '<')
			ft_redirect_here_doc();
		else
			new->type = RE_INPUT;
	}
	else if (word->word[word->re_idx] == '>')
	{
		if (word->word[++(word->re_idx)] == '>')
			new->type = RE_APPEND;
		else
			new->type = RE_OUTPUT;
	}
	if (new->type != RE_HERE)
		ft_put_redir_file_name_erase_word(new, word);
}

static void	ft_append_new_redirect_struct(t_p_data *pdata)
{
	t_redir	*tmp;

	if (pdata->now->redir == NULL)
	{
		pdata->now->redir = (t_redir *)malloc(sizeof(t_redir));
		if (!pdata->now->redir)
			ft_allocation_error();
		pdata->now->redir->next = NULL;
		ft_memset(pdata->now->redir, '\0', PATH_MAX);
	}
	else
	{
		tmp = pdata->now->redir;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_redir *)malloc(sizeof(t_redir));
		if (!tmp->next)
			ft_allocation_error();
		tmp->next->next = NULL;
		ft_memset(tmp->next, '\0', PATH_MAX);
	}
}
