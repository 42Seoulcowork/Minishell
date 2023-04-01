#include "../../includes/minishell.h"



// void	print_token(t_token *token)
// {
// 	int	i;

// 	if (!token)
// 		return ;
// 	i = 0;
// 	while (token->cmd && token->cmd[i])
// 	{
// 		printf("[%d] : \"%s\" (redir : %s)\n", i, token->cmd[i],
// 			(token->rdirs ? token->rdirs->file_name : "NULL"));
// 		i++;
// 	}
// 	t_redir *rdirs = token->rdirs;
// 	while (rdirs)
// 	{
// 		printf("[%d] : \"%s\" (redir : %s)\n", i, "",
// 			(rdirs->file_name ? rdirs->file_name : "NULL"));
// 		i++;
// 		rdirs = rdirs->next;
// 	}
// 	if (token->next)
// 		printf("\n");
// }

// void	print_queue(t_p_data *queue)
// {
// 	t_token	*tmp;

// 	tmp = queue->front;
// 	if (queue == NULL)
// 		return ;
// 	while (tmp != NULL)
// 	{
// 		print_token(tmp);
// 		tmp = tmp->next;
// 	}
// }

// size_t	ft_strnlen(const char *s, size_t maxlen)
// {
// 	size_t	len;

// 	len = 0;
// 	while (len < maxlen && s[len] != '\0')
// 		len++;
// 	return (len);
// }

// char	*ft_strndup(const char *s, size_t n)
// {
// 	size_t	len;
// 	char	*dup;

// 	len = ft_strnlen(s, n);
// 	dup = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!dup)
// 		return (NULL);
// 	dup[len] = '\0';
// 	return (ft_memcpy(dup, s, len));
// }
