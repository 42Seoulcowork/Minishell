#include "minishell.h"

static int	handle_redir(t_redir *redir)
{
	int fd;

	while (redir != NULL)
	{
		if (redir->type == RE_INPUT)
		{
			fd = open(redir->file_name, O_RDONLY);
			if (fd == -1) {
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->file_name, STDERR_FILENO);
				if (!access(redir->file_name, F_OK))
					ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
				else
					ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
				return (FALSE);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == RE_OUTPUT) // TODO 권한 줬다뺐다 해봐
		{
			if (access(redir->file_name, W_OK) && !access(redir->file_name, F_OK))
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->file_name, STDERR_FILENO);
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
				return (FALSE);
			}
			fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC , 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == RE_APPEND)
		{
			if (access(redir->file_name, W_OK) && !access(redir->file_name, F_OK))
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(redir->file_name, STDERR_FILENO);
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
				return (FALSE);
			}
			fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	return (TRUE);
}

void	run_builtin(t_env_node *head, t_token *token)
{
	if (token->cmd_type == ECHO_FUNC)
		ft_echo(head, token->cmd);
	else if (token->cmd_type == CD_FUNC)
		ft_cd(head, token->cmd);
	else if (token->cmd_type == PWD_FUNC)
		ft_pwd(head);
	else if (token->cmd_type == EXPORT_FUNC)
		ft_export(head, token->cmd);
	else if (token->cmd_type == UNSET_FUNC)
		ft_unset(head, token->cmd);
	else if (token->cmd_type == ENV_FUNC)
		ft_env(head);
	else if (token->cmd_type == EXIT_FUNC)
		ft_exit(head, token->cmd);
}

void	execute(t_env_node *head, t_p_data *p_data)
{
	int	stdin_dup;
	int	stdout_dup;


	stdin_dup = dup(STDIN_FILENO);
	stdout_dup = dup(STDOUT_FILENO);
	if (p_data->pipe_cnt == 0)
	{
		if (p_data->front->redir != NULL)
		{
			if (handle_redir(p_data->front->redir) == FALSE)
			{
				head->value = "1";
				return ;
			}
		}
		if (p_data->front->cmd_type != EXTERN_FUNC)
			run_builtin(head, p_data->front);
		else
			run_cmd(head, p_data->front);
	}
	else
	{
		//?
	}
	dup2(stdin_dup, STDIN_FILENO);
	dup2(stdout_dup, STDOUT_FILENO);
	close(stdin_dup);
	close(stdout_dup);
}