#ifndef PARSER_H
# define PARSER_H

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_SEMICOLON,
	T_NEWLINE,
	T_EOF,
}	t_token_type;

typedef enum e_redir_type
{
	RE_INPUT,
	RE_OUTPUT,
	RE_APPEND,
	RE_HERE,
}	t_redir_type;

typedef struct s_redir
{
	int					target_fd;
	char				*file_name;
	enum e_redir_type	redir_type;
	struct s_redir		*next;
}	t_redir;

typedef struct s_token
{
	char				**cmd;
	struct s_redir		*rdirs;
	struct s_token		*next;
}	t_token;

typedef struct s_parsed_data
{
	int				size;
	struct s_token	*front;
	struct s_token	*rear;
}	t_parsed_data;

t_parsed_data	tokenize(char *input);
t_token			*create_new_token(char *cmd, t_redir *rdirs);
t_token			*create_token(char **cmd, t_redir *rdirs);
void			init_tokenizer(t_parsed_data *data, t_token **token);
void			print_queue(t_parsed_data *queue);
void			enqueue(t_parsed_data *data, t_token *token);
t_token			*tokendequeue(t_parsed_data *data);
t_parsed_data	*parsing(char *str);

#endif