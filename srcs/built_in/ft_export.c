#include "minishell.h"

static size_t	arr_len(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static t_env_node	*get_old_key_address(t_env_node *head, char *key)
{
	head = head->next;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

static char	**ft_simple_split(char *tmp, char *equal_address)
{
	char	**str;
	int		i;
	int		j;

	i = 0;
	str = malloc(sizeof(char *) * 3);
	str[0] = malloc(sizeof(char) * (equal_address - tmp + 1));
	str[1] = malloc(sizeof(char) * (ft_strlen(tmp) - (equal_address - tmp) + 1));
	str[2] = NULL;
	while (tmp + i < equal_address)
	{
		str[0][i] = tmp[i];
        ++i;
    }
    str[0][i] = '\0';
    if (str[0][i - 1] == '+')
        str[0][i - 1] = '\0';
    j = 0;
	++i;
	while (*(tmp + i) != '\0')
	{
		str[1][j] = tmp[i];
		++i;
		++j;
	}
	str[1][j] = '\0';
	return (str);
}

static int	is_valid_name(char *cmd, int *is_addition_assignment)
{
	int	i;

	i = 0;
	if (!ft_isalpha(cmd[i]) && cmd[i] != '_')
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (0);
	}
	++i;
	while (cmd[i] != '\0' && cmd[i] != '=')
	{
        if (cmd[i] == '+' && cmd[i + 1] == '=')
        {
            *is_addition_assignment = 1;
            return (1);
        }
		else if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (0);
		}
		++i;
	}
	return (1);
}

void	ft_export(t_env_node *head, char **cmd)
{
	int			i;
	char 		**arr;
	char 		*tmp;
	t_env_node	*old_key;
    int         is_addition_assignment;

	i = 0;
    is_addition_assignment = 0;
	if (cmd[1] == NULL)
	{
		arr = convert_array(head);
		quick_sort(arr, 0, arr_len(arr) - 1);
		while (arr[i])
		{
			printf("declare -x %s\n", arr[i]);
			++i;
		}
		return ;
	}
	i = 1;
	while (cmd[i])
	{
		tmp = ft_strchr(cmd[i], '=');
		if (!is_valid_name(cmd[i], &is_addition_assignment))
		{
			// TODO exit_status 1로 변경
			++i;
			continue;
		}
		if (tmp == NULL)
		{
			old_key = get_old_key_address(head, cmd[i]);
			if (old_key == NULL)
				add_node(head, create_node(cmd[i], NULL));
		}
		else
		{
			if (*(tmp + 1) != '\0')
			{
				arr = ft_simple_split(cmd[i], tmp);
				old_key = get_old_key_address(head, arr[0]);
				if (old_key == NULL)
					add_node(head, create_node(arr[0], arr[1]));
                else if (is_addition_assignment)
                {
                    tmp = ft_strjoin(old_key->value, arr[1]);
                    free(old_key->value);
                    old_key->value = tmp;
                }
				else
					old_key->value = arr[1];
			}
			else
			{
				*tmp = '\0';
                if (is_addition_assignment)
                    *(tmp - 1) = '\0';
				old_key = get_old_key_address(head, cmd[i]);
				if (old_key == NULL)
					add_node(head, create_node(cmd[i], ft_strdup("")));
				else if (!is_addition_assignment)
					old_key->value = "";
			}
		}
		++i;
	}
}
