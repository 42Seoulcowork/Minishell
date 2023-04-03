#include "minishell.h"

static void	ft_find_cmd_type(t_p_data *pdata, char *new_word);

void	ft_clear_word_struct(t_word *word)
{
	word->dq_stt = OFF;
	word->sq_stt = OFF;
	word->type = NONE;
	word->word_idx = -1;
	word->break_flag = OFF;
	ft_memset(word, '\0', ARG_MAX);
}

void	ft_handle_present_word_to_token(t_p_data *pdata, t_word *word)
{
	t_redir	*present_redir;
	t_redir	*temp;

	if (word->type == COMMAND)
		ft_append_cmd_to_token(pdata, word);
	else if (word->type != NONE)
	{
		present_redir = (t_redir *)malloc(sizeof(t_redir));
		if (!present_redir)
			ft_allocation_error();
		present_redir->next = NULL;
		temp = pdata->now->redir;
		if (!temp)
			pdata->now->redir = present_redir;
		else
		{
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = present_redir;
		}
		present_redir->type = word->type;
		ft_strlcpy(present_redir->file_name, word->word, PATH_MAX);
	}
}
/* here-doc should make un-named file & save path in word[ARG_MAX] */
/* word->type == RE_TYPE : create_redic_struct , present_redic_word_to_token */

void	ft_append_cmd_to_token(t_p_data *pdata, t_word *word)
{
	char	**new_cmd;
	char	**temp;
	char	*new_word;
	int		i;

	new_cmd = (char **)malloc(sizeof(char *) * (ft_strlen(pdata->now->cmd) + 2));
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

static void	ft_find_cmd_type(t_p_data *pdata, char *new_word)
{
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
