#include "../../includes/minishell.h"

void	ft_expension_process(char **input, t_word *word, t_env_node *node)
{
	char	*tmp;
    int		i;

    i = -1;
	if (*(*input + 1) == ' ' || *(*input + 1) == '|' || *(*input + 1) == '\n')
		word->word[++(word->word_idx)] = '$';
	else
    {
        (*input) += 1;
        tmp = ft_strlen_for_exp(input);
        while (node)
		{
            if (ft_strcmp(tmp, node->key) == 0)
			{
                while ((node->value)[++i])
                    (word->word)[++(word->word_idx)] = node->value[i];
                break;
            }
            node = node->next;
        }
        free(tmp);
        if (node == NULL)
        {
            i = 1;
            while ((*input)[i] == ' ')
                ++i;
            if ((*input)[i] == '|')
                (*input) += i;
        }
    }
}
