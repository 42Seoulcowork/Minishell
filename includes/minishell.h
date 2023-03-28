#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include "../lib/libft.h"

# include "parser.h"

# define READ_END 0
# define WRITE_END 1

typedef enum s_erroridx {
	PIPE_ERROR,
	FORK_ERROR,
	MALLOC_ERROR,
	COMMAND_ERROR,
	RUN_ERROR,
	PERMISSION_ERROR,
	EXIT_PERMOSSION_ERROR = 126,
	EXIT_COMMAND_ERROR = 127,
}	t_erroridx;

typedef struct s_envp{
	int		stdin_dup;
	int		stdout_dup;
	int		exit_status;
	int		argc;
	char	**argv;
	char	**paths;
	char	**envp;
	pid_t	main_pid;
}			t_envp;

typedef struct s_env_node
{
    char				*key;
    char				*value;
    struct s_env_node	*next;
}   t_env_node;

/* built_in */
void		ft_pwd(void);
void		ft_exit(char **args);
void		ft_echo(char **args);
void		ft_env(t_env_node *head);
void		ft_cd(char **argv, t_envp *tenvp);
void		ft_export(t_env_node *head, char **cmd);

/* execute */
void		envp_init(t_envp *tenvp, char **envp);
void		run_cmd(char *str, t_envp *tenvp);
void		pipex(char *str, t_envp *tenvp);
char		**exception2(int i, t_envp *tenvp);
char		**exception(int i, t_envp *tenvp, char *cmd);
char		**argv_init(int i, t_envp *tenvp);
void		work_pid(int argc, t_envp *tenvp);
void		error(int errnum, char *problem, t_envp *tenvp);
char		**path_init(t_envp *tenvp);
char		*ft_path(char *filename, char **path_option);
void		check_str(int flag, char **new_argv);
char		**ft_split_set(char *str, char *charset);
t_env_node	*create_node(char *key, char *value);
t_env_node	*init_node(char **envp);
void		add_node(t_env_node *head, t_env_node *node);
t_env_node	*copy_list(t_env_node *head);
char		**convert_array(t_env_node *head);
void		quick_sort(char **arr, size_t left, size_t right);

#endif
