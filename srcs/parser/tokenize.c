#include "minishell.h"

t_redir	*create_new_redir(int target_fd, t_r_type redir_type)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->target_fd = target_fd;
	redir->file_name = NULL;
	redir->redir_type = redir_type;
	redir->next = NULL;
	return (redir);
}

int	get_digit_count(const char *str)
{
	int	count;

	count = 0;
	while (ft_isdigit(*str))
	{
		count++;
		str++;
	}
	return (count);
}

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen && s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;

	len = ft_strnlen(s, n);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	dup[len] = '\0';
	return (ft_memcpy(dup, s, len));
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
	t_p_data	data;
	t_token		*token;
	t_redir		*rdirs;
	char		*word;
	char		*tmp;
	char		*str;
	int			state;

	str = input;
	init_tokenizer(&data, &token);
	if (!input)
		return (data);
	rdirs = NULL;
	word = ft_strdup("");
	state = 0;
	while (*input)
	{
		if (*input == '\n')
			break ;
		else if (*input == '<' || *input == '>')
		{
			tmp = NULL;
			if (input != str && !ft_isspace(*(input - 1)))
			{
				if (*(input + 1) && ft_isdigit(*(input + 1)))
				{
					tmp = ft_strndup(input + 1, get_digit_count(input + 1));
					rdirs = create_new_redir(*input == '<' ? STDIN_FILENO : STDOUT_FILENO,
                         *input == '<' ? RE_INPUT : RE_OUTPUT);
					free(tmp);
					input += get_digit_count(input + 1) + 1;
				}
				else
					input++;
			}
			else
				input++;
		}
		else if (ft_isspace(*input))
			input++;
		else if (*input == '|')
		{
			enqueue(&data, create_new_token(ft_strdup("|"), NULL));
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
