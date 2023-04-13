#include "minishell.h"

static int	ft_here_doc_pretreatment(t_p_data *pdata, \
t_redir *new, t_word *word, int i)
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
	tmp = ft_strjoin_s(".tmp", str);
	free(str);
	new->heredoc_fd = open(tmp, O_RDWR | O_CREAT, 0644);
	if (new->heredoc_fd == -1)
		ft_open_error();
	while (tmp[++i])
		new->file_name[i] = tmp[i];
	free(tmp);
	return (0);
}

static void	ft_here_doc_act(t_p_data *pdata, t_redir *new, char *tmp)
{
	char	*str;

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
}

int	ft_redirect_here_doc(t_p_data *pdata, t_redir *new, t_word *word)
{
	char	*tmp;

	if (ft_here_doc_pretreatment(pdata, new, word, -1) == 1)
		return (1);
	tmp = ft_strdup_s(word->word + word->re_idx);
	word->re_idx -= 2;
	while (word->word[word->re_idx])
		word->word[(word->re_idx)++] = '\0';
	ft_here_doc_act(pdata, new, tmp);
	close(new->heredoc_fd);
	new->heredoc_fd = open(new->file_name, O_RDONLY);
	if (new->heredoc_fd == -1)
		ft_open_error();
	unlink(new->file_name);
	return (0);
}
