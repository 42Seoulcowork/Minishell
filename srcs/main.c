#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_p_data	parsed_data;
	t_env_node	*head;

	head = init_node(envp);
	if (ac != 1)
		return (0);
	if (!ft_strcmp(av[0], "minishell"))
		return (0);
	//signal_setting();
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		parsing(str, &parsed_data, head);
		execute(head, &parsed_data);
		if (str[0] != '\0')
			add_history(str);
		printf("exit_status: %s\n", head->value);
		free(str);
	}
	return (0);
}
// 		parsed_data.front = malloc(sizeof(t_token));
// 		parsed_data.front->cmd = ft_split(str, ' ');
// 		if (ft_strncmp("cd", str, 2) == 0)
// 			parsed_data.front->cmd_type = CD_FUNC;
// 		else if (ft_strncmp("echo", str, 4) == 0)
// 			parsed_data.front->cmd_type = ECHO_FUNC;
// 		else if (ft_strncmp("env", str, 3) == 0)
// 			parsed_data.front->cmd_type = ENV_FUNC;
// 		else if (ft_strncmp("exit", str, 4) == 0)
// 			parsed_data.front->cmd_type = EXIT_FUNC;
// 		else if (ft_strncmp("export", str, 6) == 0)
// 			parsed_data.front->cmd_type = EXPORT_FUNC;
// 		else if (ft_strncmp("unset", str, 5) == 0)
// 			parsed_data.front->cmd_type = UNSET_FUNC;
// 		else if (ft_strncmp("pwd", str, 3) == 0)
// 			parsed_data.front->cmd_type = PWD_FUNC;
// //		else
// //			parsed_data.front->cmd_type = EXTERN_FUNC;
// 		parsed_data.front->cmd_type = EXTERN_FUNC;
// 		parsed_data.front->cmd = ft_split("ls", ' ');
// 		parsed_data.front->redir = NULL;
// //		parsed_data.front->redir->next = malloc(sizeof(t_redir));
// //		parsed_data.front->redir->next->file_name[0] = 'b';
// //		parsed_data.front->redir->next->type = RE_OUTPUT;
// //		parsed_data.front->redir->next->next = malloc(sizeof(t_redir));
// //		parsed_data.front->redir->next->next->file_name[0] = 'c';
// //		parsed_data.front->redir->next->next->type = RE_OUTPUT;
// //		parsed_data.front->redir->next->next->next = malloc(sizeof(t_redir));
// //		parsed_data.front->redir->next->next->next->file_name[0] = 'd';
// //		parsed_data.front->redir->next->next->next->type = RE_INPUT;
// //		parsed_data.front->redir->next->next->next->next = NULL;
// 		parsed_data.front->next = malloc(sizeof(t_token));
// 		parsed_data.front->next->cmd_type = EXTERN_FUNC;
// 		parsed_data.front->next->cmd = ft_split("grep srcs", ' ');
// 		parsed_data.front->next->redir = NULL;
// 		parsed_data.front->next->next = NULL;

// //		parsed_data.front->next->next = malloc(sizeof(t_token));
// //		parsed_data.front->next->next->cmd_type = EXTERN_FUNC;
// //		parsed_data.front->next->next->cmd = ft_split("cat", ' ');
// //		parsed_data.front->next->next->redir = NULL;
// //		parsed_data.front->next->next->next = malloc(sizeof(t_token));
// //		parsed_data.front->next->next->next->cmd_type = EXTERN_FUNC;
// //		parsed_data.front->next->next->next->cmd = ft_split("cat", ' ');
// //		parsed_data.front->next->next->next->redir = NULL;
// //		parsed_data.front->next->next->next->next = NULL;
// 		  // 테스트를 위한 실행팀의 발버둥
// //		parsed_data.front->redir = malloc(sizeof(t_redir));
// //		parsed_data.front->redir->type = RE_INPUT;
// //		parsed_data.front->redir->file_name[0] = 'b';
// //		parsed_data.front->redir->next = malloc(sizeof(t_redir));
// //		parsed_data.front->redir->next->type = RE_OUTPUT;
// //		parsed_data.front->redir->next->file_name[0] = 'x';
// //		parsed_data.front->redir->next->next = malloc(sizeof(t_redir));
// //		parsed_data.front->redir->next->next->type = RE_OUTPUT;
// //		parsed_data.front->redir->next->next->file_name[0] = 'f';
// //		parsed_data.front->redir->next->next->next = malloc(sizeof(t_redir));
// //		parsed_data.front->redir->next->next->next->type = RE_APPEND;
// //		parsed_data.front->redir->next->next->next->file_name[0] = 'e';
// //		parsed_data.front->redir->next->next->next->next = malloc(sizeof(t_redir));
// //		parsed_data.front->redir->next->next->next->next->type = RE_INPUT;
// //		parsed_data.front->redir->next->next->next->next->file_name[0] = 'j';
// //		parsed_data.front->redir->next->next->next->next->next = NULL;
