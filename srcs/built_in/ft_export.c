#include "minishell.h"

static int	is_valid_name(char *cmd, int *is_addition_assignment)
{
	int	i;

	i = 0;
	if (!ft_isalpha(cmd[i]) && cmd[i] != '_')
		return (print_error_for_invalid_name(cmd));
	++i;
	while (cmd[i] != '\0' && cmd[i] != '=')
	{
		if (cmd[i] == '+' && cmd[i + 1] == '=')
		{
			*is_addition_assignment = 1;
			return (1);
		}
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (print_error_for_invalid_name(cmd));
		++i;
	}
	return (1);
}

static void	export_with_value(t_env_node *head, char *tmp, char *cmd, \
								int is_addition_assignment)
{
	char		**arr;
	t_env_node	*old_key;

	arr = ft_simple_split(cmd, tmp);
	old_key = get_old_key_address(head, arr[0]);
	if (old_key == NULL)
		add_node(head, create_node(arr[0], arr[1]));
	else if (is_addition_assignment)
	{
		tmp = ft_strjoin_s(old_key->value, arr[1]);
		free(old_key->value);
		old_key->value = tmp;
	}
	else
		old_key->value = arr[1];
}

static void	export_with_equal(t_env_node *head, char *tmp, char *cmd, \
								int is_addition_assignment)
{
	t_env_node	*old_key;

	if (*(tmp + 1) != '\0')
		export_with_value(head, tmp, cmd, is_addition_assignment);
	else
	{
		*tmp = '\0';
		if (is_addition_assignment)
			*(tmp - 1) = '\0';
		old_key = get_old_key_address(head, cmd);
		if (old_key == NULL)
			add_node(head, create_node(cmd, ft_strdup("")));
		else if (!is_addition_assignment)
			old_key->value = "";
	}
}

static void	export_without_equal(t_env_node *head, char *cmd)
{
	t_env_node	*old_key;

	old_key = get_old_key_address(head, cmd);
	if (old_key == NULL)
		add_node(head, create_node(cmd, NULL));
}

void	ft_export(t_env_node *head, char **cmd)
{
	int			i;
	int			is_addition_assignment;
	char		*tmp;

	is_addition_assignment = 0;
	g_exit_status = 0;
	if (cmd[1] == NULL)
		return (print_export(head));
	i = 1;
	while (cmd[i])
	{
		tmp = ft_strchr(cmd[i], '=');
		if (!is_valid_name(cmd[i], &is_addition_assignment))
		{
			++i;
			g_exit_status = 1;
			continue ;
		}
		if (tmp == NULL)
			export_without_equal(head, cmd[i]);
		else
			export_with_equal(head, tmp, cmd[i], is_addition_assignment);
		++i;
	}
}
