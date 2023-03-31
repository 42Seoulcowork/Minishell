#ifndef PARSER_H
# define PARSER_H

# define PATH_MAX 4096
# define ARG_MAX 262144
# define ON 1
# define OFF 0

typedef enum e_type
{
	RE_INPUT,
	RE_HERE,
	RE_OUTPUT,
	RE_APPEND,
	COMMAND,
	NONE
}	t_type;

typedef enum e_c_type
{
	EXTERN_FUNC,
	ECHO_FUNC,
	CD_FUNC,
	PWD_FUNC,
	EXPORT_FUNC,
	UNSET_FUNC,
	ENV_FUNC,
	EXIT_FUNC
}	t_c_type;

typedef struct s_redir
{
	t_type			type;
	char			file_name[PATH_MAX];
	struct s_redir	*next;
}	t_redir;

typedef struct s_token
{
	char			**cmd;
	t_c_type		cmd_type;
	t_redir			*redir;
	struct s_token	*next;
}	t_token;

typedef struct s_p_data
{
	int				pipe_cnt;
	struct s_token	*front;
	struct s_token	*rear;
}	t_p_data;

typedef struct s_word
{
	int			sq_state;
	int			dq_state;
	t_type		type;
	int			break_flag;
	char		word[ARG_MAX];
}	t_word;


t_p_data	tokenize(char *input);
void		parsing(char *str, t_p_data *pdata);
t_token		*create_token(char **cmd, t_redir *rdirs);
t_token		*create_new_token(char *cmd, t_redir *rdirs);

void		enqueue(t_p_data *data, t_token *token);
t_token		*dequeue(t_p_data *data);

void		print_queue(t_p_data *queue);

#endif