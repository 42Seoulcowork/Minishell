#include "../../includes/minishell.h"

static void	ft_append_new_redirect_struct(t_p_data *pdata);
static void	ft_put_re_put_del_word(t_redir *new, t_word *word, int tmp_idx);

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
			ft_redirect_here_doc(new, word, tmp_idx);
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
		ft_put_re_put_del_word(new, word, tmp_idx);
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

static void	ft_redirect_here_doc(t_redir *new, t_word *word, int tmp_idx)
{
	++(word->re_idx);
	while (word->word[word->re_idx] == ' ')
		word->re_idx += 1;
	if (word->word[word->re_idx] == '>' || word->word[word->re_idx] == '<' \
	|| word->word[word->re_idx] == '|' || word->word[word->re_idx] == '\n')
	
}

static void	ft_put_re_put_del_word(t_redir *new, t_word *word, int tmp_idx)
{
	int	i;

	i = -1;
	if (new->type == RE_APPEND)
		word->re_idx += 1;
	while (word->word[word->re_idx] == ' ')
		word->re_idx += 1;
	if (word->word[word->re_idx] == '>' || word->word[word->re_idx] == '<' \
	|| word->word[word->re_idx] == '|' || word->word[word->re_idx] == '\n')
		ft_redirect_syntax_error();
	while (word->re_idx <= word->word_idx)
	{
		new->file_name[++i] = word->word[word->re_idx];
		word->re_idx += 1;
	}
	while (tmp_idx <= word->word_idx)
	{
		word->word[tmp_idx] = '\0';
		tmp_idx += 1;
	}
}
