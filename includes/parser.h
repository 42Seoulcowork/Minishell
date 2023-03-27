#ifndef PARSER_H
# define PARSER_H

typedef enum e_ttype
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_SEMICOLON,
	T_NEWLINE,
	T_EOF,
}	t_ttype;

typedef enum e_rtype
{
	RE_INPUT,
	RE_OUTPUT,
	RE_APPEND,
	RE_HERE,
}	t_rtype;

typedef struct s_token
{
	char			*str;
	enum e_ttype	type;
	char			*redir_file;
	enum e_rtype	redir_type;
	struct s_token	*next;
}	t_token;

typedef struct s_rdr
{
	char	*type;
	char	*file_name;
}	t_rdr;

typedef struct s_cmdline
{
	char			*path;
	char			**cmd;
	struct s_rdr	rdr;
}	t_cmdline;

typedef struct s_node
{
	struct s_cmdline	cmdline;
	struct s_node		*next;
}	t_node;

typedef struct s_queue
{
	int				size;
	struct s_node	*front;
	struct s_node	*rear;
}	t_queue;

t_token	*tokenize(char *str);
void	print_tokens(t_token *tokens);

#endif