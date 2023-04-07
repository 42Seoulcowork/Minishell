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
void		ft_pwd(void);
void		ft_exit(char **args);
void		ft_echo(char **args);
void		ft_env(t_env_node *head);
void		ft_cd(t_env_node *head, char **argv);
void		ft_export(t_env_node *head, char **cmd);
void		ft_unset(t_env_node *head, char **keys);
char		*ft_getenv(t_env_node *head, char *key);

/* execute */
t_env_node	*create_node(char *key, char *value);
t_env_node	*init_node(char **envp);
void		add_node(t_env_node *head, t_env_node *node);
void		delete_node(t_env_node *head, char *key);
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

int			ft_pipe(int fd[2]);
int			ft_fork(void);

#endif
