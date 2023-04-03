#include "../../includes/minishell.h"

void	ft_redirect_here_doc(t_redir *new, t_word *word, int tmp_idx)
{
	++(word->re_idx);
	while (word->word[word->re_idx] == ' ')
		word->re_idx += 1;
	if (word->word[word->re_idx] == '>' || word->word[word->re_idx] == '<' \
	|| word->word[word->re_idx] == '|' || word->word[word->re_idx] == '\n')
		return ;
}
