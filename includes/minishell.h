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
# include <fcntl.h>

# include "../lib/libft.h"
# include "parser.h"

# define READ_END 0
# define WRITE_END 1
# define TRUE	1
# define FALSE	0

int	g_exit_status;

/* built_in */

void		ft_pwd(t_env_node *head);
void		ft_exit(char **args);
void		ft_echo(char **args);
void		ft_env(t_env_node *head);
void		ft_cd(t_env_node *head, char **argv);
void		ft_export(t_env_node *head, char **cmd);
void		ft_unset(t_env_node *head, char **keys);
char		*ft_getenv(t_env_node *head, char *key);
char		**ft_simple_split(char *tmp, char *equal_address);
int			print_error_for_invalid_name(char *cmd);
void		print_export(t_env_node *head);
t_env_node	*get_old_key_address(t_env_node *head, char *key);

/* execute */

t_env_node	*create_node(char *key, char *value);
t_env_node	*init_node(char **envp);
void		delete_node(t_env_node *head, char *key);
void		add_node(t_env_node *head, t_env_node *node);
char		**convert_array_for_export(t_env_node *head);
char		**convert_array_for_execve(t_env_node *head);
void		execute(t_env_node *head, t_p_data *p_data);
void		run_cmd(t_env_node *head, t_token *token);
int			handle_redir(t_redir *redir);
void		quick_sort(char **arr, int left, int right);
void		execute_token(t_env_node *head, t_token *token);

/* execute_pipe */

int			execute_no_pipe(t_env_node *head, t_p_data *p_data, int *status);
void		execute_first_pipe(t_env_node *head, t_p_data *p_data, int **fd);
int			execute_middle_pipe(t_env_node *head, t_p_data *p_data, int **fd);
int			execute_end_pipe(t_env_node *head, t_p_data *p_data, int **fd, int i);

int			pipe_s(int fd[2]);
int			fork_s(void);
void		*malloc_s(size_t size);
char		*ft_strjoin_s(char const *s1, char const *s2);
char		*ft_strdup_s(const char *s1);
char		**ft_split_s(char const *s, char c);


#endif
