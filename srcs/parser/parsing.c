#include "minishell.h"

void	parsing(char *str, t_p_data *pdata)
{
	t_word	word;

	ft_init_token_word(pdata, &word);
	ft_tokenize(pdata, &word);
}

void	ft_init_token_word(t_p_data *pdata, t_word *word)
{

	data->size = 0;
	data->front = NULL;
	data->rear = NULL;
	*token = NULL;
}