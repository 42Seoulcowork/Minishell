#include "minishell.h"

static void	ft_find_cmd_type(t_p_data *pdata, char *new_word);

void	ft_clear_word_struct(t_word *word)
{
	word->dq_stt = OFF;
	word->sq_stt = OFF;
	word->ex_stt = OFF;
	word->ex_idx = -1;
	word->re_stt = OFF;
	word->re_idx = 0;
	word->word_idx = -1;
	word->break_flag = OFF;
	ft_memset(word, '\0', ARG_MAX);
}

void	ft_handle_present_w_cmd_to_token(t_p_data *pdata, t_word *word)
{
	char	**new_cmd;
	char	**temp;
	char	*new_word;
	size_t	i;

	if (word->word[0] == '\0')
		return ;
	new_cmd = (char **)malloc(sizeof(char *) \
		* ft_strlen(*(pdata->now->cmd) + 2));
	i = 0;
	while (i < ft_strlen(*(pdata->now->cmd)))
	{
		new_cmd[i] = (pdata->now->cmd)[i];
		++i;
	}
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

static void	ft_find_cmd_type(t_p_data *pdata, char *new_word)
{
	int	i;

	i = -1;
	while (new_word[++i])
		new_word[i] = ft_tolower(new_word[i]);
	if (!ft_strcmp(new_word, "echo"))
		pdata->now->cmd_type = ECHO_FUNC;
	else if (!ft_strcmp(new_word, "cd"))
		pdata->now->cmd_type = CD_FUNC;
	else if (!ft_strcmp(new_word, "pwd"))
		pdata->now->cmd_type = PWD_FUNC;
	else if (!ft_strcmp(new_word, "export"))
		pdata->now->cmd_type = EXPORT_FUNC;
	else if (!ft_strcmp(new_word, "unset"))
		pdata->now->cmd_type = UNSET_FUNC;
	else if (!ft_strcmp(new_word, "env"))
		pdata->now->cmd_type = ENV_FUNC;
	else if (!ft_strcmp(new_word, "exit"))
		pdata->now->cmd_type = EXIT_FUNC;
	else
		pdata->now->cmd_type = EXTERN_FUNC;
}

void	ft_clear_all_pdata(t_p_data *pdata)
{
	t_redir	*tmp;
	int		i;

	pdata->pipe_cnt = 0;
	i = -1;
	while (pdata->front)
	{
		pdata->now = pdata->front;
		while (pdata->front->redir)
		{
			tmp = pdata->front->redir;
			pdata->front->redir = pdata->front->redir->next;
			free(tmp);
		}
		while (pdata->front->cmd[++i])
			free(pdata->front->cmd[i]);
		free(pdata->front->cmd);
		pdata->front = pdata->front->next;
		free(pdata->now);
	}
	pdata->now = NULL;
}
