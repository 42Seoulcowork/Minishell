#include "../../includes/minishell.h"

void	ft_redirect_here_doc(t_redir *new, t_word *word, int tmp_idx)
{
	char	*tmp;
	char	*str;
	int		flag;
	int		fd;

	word->re_idx += 1;
	while (word->word[word->re_idx] == ' ')
		word->re_idx += 1;
	if (word->word[word->re_idx] == '>' || word->word[word->re_idx] == '<' \
	|| word->word[word->re_idx] == '(' || word->word[word->re_idx] == ')' \
	|| word->word[word->re_idx] == '`' || word->word[word->re_idx] == '&')
		ft_stx_near_unexp_tk_error(word->word[word->re_idx]);
	// fd = open(unnamed file);
	// new->filename = unnamed file
	tmp = ft_strdup(word->word + word->re_idx);
	flag = 0;
	while (flag == 0)
	{
		str = readline("> ");
		if (!str)
			ft_eof_handling();
		if (ft_strcmp(tmp, str) == 0)
			break ;
		// else
		// 		append string in the unnamed file;
		// free str
	}
	// fd store in anyway (for unlink)
}

void	ft_append_cmd_to_token(t_p_data *pdata, t_word *word)
{
	char	**new_cmd;
	char	**temp;
	char	*new_word;
	int		i;

	if (word->word[0] == '\0')
		return ;
	new_cmd = (char **)malloc(sizeof(char *) \
		* (ft_strlen(pdata->now->cmd) + 2));
	i = -1;
	while (++i < ft_strlen(pdata->now->cmd))
		new_cmd[i] = (pdata->now->cmd)[i];
	new_word = ft_strdup(word->word);
	if (!new_word)
		ft_allocation_error();
	if (i == 0)
		ft_find_cmd_type(pdata, new_word);
	new_cmd[i] = new_word;
	new_cmd[i + 1] = NULL;
	temp = pdata->now->cmd;
	pdata->now->cmd = new_cmd;
	free(temp);
}
