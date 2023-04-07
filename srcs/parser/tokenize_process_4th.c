#include "minishell.h"

static void	ft_here_doc_pretreatment(t_redir *new, t_word *word)
{
	char	*str;
	char	*tmp;

	new->type = RE_HERE;
	word->re_idx += 1;
	if (word->word[word->re_idx] == '>' || word->word[word->re_idx] == '<' \
	|| word->word[word->re_idx] == '(' || word->word[word->re_idx] == ')' \
	|| word->word[word->re_idx] == '`' || word->word[word->re_idx] == '&')
		ft_stx_near_unexp_tk_error();
	str = ft_itoa(++(word->tmp_num));
	if (!str)
		ft_allocation_error();
	tmp = ft_strjoin(".tmp", str);
	if (!tmp)
		ft_allocation_error();
	free(str);
	new->heredoc_fd = open(tmp, O_RDWR | O_CREAT, 0644);
	if (!new->heredoc_fd)
		ft_open_error();
	unlink(tmp);
	free(tmp);
}

void	ft_redirect_here_doc(t_p_data *pdata, t_redir *new, t_word *word)
{
	char	*tmp;
	char	*str;

	ft_here_doc_pretreatment(new, word);
	tmp = ft_strdup(word->word + word->re_idx);
	if (!tmp)
		ft_allocation_error();
	while (1)
	{
		str = readline("> ");
		if (!str)
			ft_clear_all_pdata(pdata);
		if (ft_strcmp(tmp, str) == 0)
		{
			free(str);
			break ;
		}
		else
		{
			write(new->heredoc_fd, str, ft_strlen(str));
			write(new->heredoc_fd, "\n", 1);
		}
		free(str);
	}
}
