#include "minishell.h"

static int	ft_here_doc_pretreatment(t_p_data *pdata, \
t_redir *new, t_word *word)
{
	char	*str;
	char	*tmp;
	char	temp;

	word->re_idx += 1;
	temp = word->word[word->re_idx];
	if (temp == '>' || temp == '<' || temp == '(' || temp == ')' 
	|| temp == '`' || temp == '&' || temp == '\0')
	{
		ft_syntax_error(pdata, word);
		return (1);
	}
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
	return (0);
}

int	ft_redirect_here_doc(t_p_data *pdata, t_redir *new, t_word *word)
{
	char	*tmp;
	char	*str;

	if (ft_here_doc_pretreatment(pdata, new, word) == 1)
		return (1);
	tmp = ft_strdup(word->word + word->re_idx);
	if (!tmp)
		ft_allocation_error();
	while (1)
	{
		str = readline("> ");
		if (!str)
			ft_clear_all_pdata(pdata);
		if (!str || ft_strcmp(tmp, str) == 0)
		{
			free(str);
			break ;
		}
		write(new->heredoc_fd, str, ft_strlen(str));
		write(new->heredoc_fd, "\n", 1);
		free(str);
	}
	return (0);
}
