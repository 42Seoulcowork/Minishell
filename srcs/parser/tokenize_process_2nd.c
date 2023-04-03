#include "../../includes/minishell.h"

void	ft_start_expansion_stt(char **input, t_word *word)
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
		(word->word)[++(word->word_idx)] = '$';
		word->ex_stt = ON;
		word->ex_idx = word->word_idx;
	}
}

static int	ft_check_dic_input_value(t_word *word, t_env_node *node, char *tmp)
{
	int	i;

	i = -1;
	if (ft_strcmp(tmp, node->key) == 0)
	{
		while ((node->value)[++i])
			(word->word)[++(word->word_idx)] = node->value[i];
		return (0);
	}
	else
		return (1);
}

void	ft_expension_process(t_word *word, t_env_node *node)
{
	char	*tmp;
	int		end_idx;

	if (word->ex_idx == word->word_idx)
		return ;
	else
	{
		tmp = ft_strdup(word->word + word->ex_idx + 1);
		end_idx = word->word_idx;
		word->word_idx = word->ex_idx;
		while (node)
		{
			if (ft_check_dic_input_value(word, node, tmp) == 0)
				break ;
			node = node->next;
		}
		free(tmp);
		if (node == NULL)
			word->word[++(word->word_idx)] = '\0';
		while (word->word_idx < end_idx)
			word->word[++(word->word_idx)] = '\0';
	}
}
