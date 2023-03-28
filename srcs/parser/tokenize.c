#include "minishell.h"

static int	is_metachar(char c)
{
	// - **`metacharacter`**
    // 따옴표 없이 단어를 구분하는 문자입니다. 메타 문자는 `space`,
	// `tab`, `newline`또는 다음 문자 중 하나입니다.
	// '|', '&', ';', '(', ')', '<', 또는 '>'.
	return (c == '|' || c == '<' || c == '>' || c == ';' || c == '\n');
}

static char	*get_word(char **line)
{
	char	*start;
	char	*word;

	start = *line;
	while (**line && !ft_isspace(**line) && !is_metachar(**line))
	{
		if (**line == '\\' && ft_strchr("$\"\\", *(*line + 1)))
			++(*line);
		++(*line);
	}
	word = ft_substr(start, 0, *line - start);
	return (word);
}

void	init_tokenizer(t_p_data *data, t_token **token)
{
	data->size = 0;
	data->front = NULL;
	data->rear = NULL;
	*token = NULL;
}

t_token	*create_new_token(char *cmd, t_redir *rdirs)
{
	char	**tokens;
	t_token	*new_token;

	if (!cmd || !*cmd)
		return (NULL);
	tokens = ft_split(cmd, ' ');
	new_token = create_token(tokens, rdirs);
	free(cmd);
	return (new_token);
}

t_p_data	tokenize(char *input)
{
	t_token			*token;
	t_p_data	data;
	t_redir			*rdirs;

	init_tokenizer(&data, &token);
	if (!input)
		return (data);
	rdirs = NULL;
	while (*input)
	{
		if (ft_isspace(*input))
			input++;
		else if (*input == '|')
		{
			enqueue(&data, create_new_token(ft_strdup("|"), NULL));
			input++;
		}
		else if (*input == '<' || *input == '>')
		{
			printf("redirect 구현해야댐\n");
			input++;
		}
		else
		{
			token = create_new_token(get_word(&input), rdirs);
			if (token)
				enqueue(&data, token);
			rdirs = NULL;
		}
	}
	return (data);
}
