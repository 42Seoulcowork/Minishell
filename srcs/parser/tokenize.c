#include "minishell.h"

static int	is_metachar(char c)
{
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

static void	add_token(t_token *tokens, t_token *new)
{
	t_token	*tmp;

	if (!tokens)
	{
		tokens = new;
		return ;
	}
	tmp = tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*create_token(char *str, t_ttype type, t_rtype rtype, char *rfile)
{
	t_token	*ret;

	ret = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!ret)
		return (NULL);
	ret->str = str;
	ret->type = type;
	ret->redir_type = rtype;
	ret->redir_file = rfile;
	ret->next = NULL;
	return (ret);
}

t_token	*tokenize(char *str)
{
	t_token	*ret;
	t_token	*token;
	char	*tmp;

	tmp = ft_strdup(str);
	ret = create_token(NULL, T_NEWLINE, 0, NULL);
	while (*tmp)
	{
		if (ft_isspace(*tmp))
			tmp++;
		else if (is_metachar(*tmp))
		{
			token = create_token(ft_substr(tmp, 0, 1), \
				(t_ttype)(*tmp)++, 0, NULL);
			add_token(ret, token);
		}
		else if (*tmp == '\'' || *tmp == '\"')
			printf("quote 처리해야댐\n");
		else
		{
			token = create_token(get_word(&tmp), T_WORD, 0, NULL);
			add_token(ret, token);
		}
	}
	token = create_token(NULL, T_EOF, 0, NULL);
	add_token(ret, token);
	return (ret);
}
