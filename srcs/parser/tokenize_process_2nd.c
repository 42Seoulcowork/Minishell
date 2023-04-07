#include "minishell.h"

void	ft_start_expansion_stt(char **input, t_word *word, t_env_node *node)
{
	int		i;
	char	*tmp;

	i = -1;
	if (*(*input + 1) == '?')
	{
		(*input) += 1;
		tmp = ft_itoa(g_exit_status);
		while (tmp[++i])
			word->word[++(word->word_idx)] = tmp[i];
		free(tmp);
	}
	else
	{
		if (word->ex_stt == ON)
			ft_expension_process(word, node);
		(word->word)[++(word->word_idx)] = '$';
		word->ex_stt = ON;
		word->ex_idx = word->word_idx;
	}
}

static int	ft_check_dic_input_value(t_word *word, t_env_node *node, char *tmp)
{
	int	temp_idx;
	int	i;

	while (node)
	{	
		if (ft_strcmp(tmp, node->key) == 0)
		{
			i = -1;
			while ((node->value)[++i])
				(word->word)[++(word->word_idx)] = node->value[i];
			break ;
		}
		node = node->next;
	}
	free(tmp);
	temp_idx = word->word_idx;
	if (node == NULL)
		word->word[++(word->word_idx)] = '\0';
	return (temp_idx);
}

void	ft_expension_process(t_word *word, t_env_node *node)
{
	char	*tmp;
	int		temp_idx;
	int		end_idx;

	if (word->ex_idx == word->word_idx)
		word->ex_stt = OFF;
	else
	{
		tmp = ft_strdup(word->word + word->ex_idx + 1);
		if (!tmp)
			ft_allocation_error();
		end_idx = word->word_idx;
		word->word_idx = word->ex_idx - 1;
		temp_idx = ft_check_dic_input_value(word, node, tmp);
		while (word->word_idx < end_idx)
			word->word[++(word->word_idx)] = '\0';
		word->word_idx = temp_idx;
		word->ex_stt = OFF;
	}
}
