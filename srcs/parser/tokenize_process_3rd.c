#include "minishell.h"

static void	ft_append_new_redirect_struct(t_p_data *pdata);
static void	ft_put_re_put_del_word(t_redir *new, t_word *word, int tmp_idx);

void	ft_start_redirect_stt(char input, t_word *word, t_env_node *node)
{
	if (word->ex_stt == ON)
		ft_expension_process(word, node);
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
			ft_redirect_here_doc(pdata, new, word);
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
	ft_put_re_put_del_word(new, word, tmp_idx);
	word->re_stt = OFF;
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
		pdata->now->redir->heredoc_fd = -1;
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

static int	ft_is_right_redirection(t_word *word)
{
	char	c;

	c = word->word[word->re_idx];
	if (c == '`' || c == '&' || c == '(' || \
		c == ')' || c == '<' || c == '>' )
		ft_stx_near_unexp_tk_error();
	else if (c == '*' && word->word[word->re_idx + 1] == '\0')
		ft_ambiguous_redirect_error();
	return (0);
}

static void	ft_put_re_put_del_word(t_redir *new, t_word *word, int tmp_idx)
{
	int	i;

	i = -1;
	if (new->type == RE_APPEND)
		word->re_idx += 1;
	if (new->type != RE_HERE)
	{
		ft_is_right_redirection(word);
		ft_strlcpy(new->file_name, word->word + word->re_idx, PATH_MAX);
	}
	while (tmp_idx <= word->word_idx)
	{
		word->word[tmp_idx] = '\0';
		tmp_idx += 1;
	}
}
