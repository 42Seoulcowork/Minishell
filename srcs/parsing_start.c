#include "libft.h"
#include <stdio.h>

/*
typedef struct 	s_line
{
	int		pipe // 있으면 1 없으면 0
	char	*path // 첫 command 저장 (예: "ls -a -l"에서 "ls")
	char	**cmd // option들을 포함한 모든 command 저장 (예: "ls -a -l"에서 "ls", "-a", "-l")
}	t_line;

typedef struct	s_cmdlist
{
	struct s_line	*line; // 위 구조체 (아래 rdlist처럼 구조체 따로 안 써도 될 것 같기도..?)
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct	s_rdlist
{
	int				size; // 총 redirection 개수 : 파이프 단위로 개수 셀 지 or 전체 command line 단위로 개수 셀 지
	int				pipe; // 몇번째 파이프인지
	char			*type; // <, <<, >, >>
	char			*obj; // rdrct 다음 단어 (예: "> infile" 에서 "infile")
	struct s_rdlist	*next;
}	t_rdlist;


static void print_cmdlist(t_cmdlist *cmd_head)
{
	t_cmdlist *current = cmd_head;

	while (current != NULL)
	{
		printf("{%s} -> ", current->path);
		current = current->next;
	}
	printf("NULL");
	printf("\n");
}

static void print_rdlist(t_rdlist *rd_head)
{
	t_rdlist *current = rd_head;

	while (current != NULL) {
		printf("{%s} -> ", type);
		current = current->next;
	}
	printf("NULL");
	printf("\n");
}

static void	append_cmd(t_cmdlist **cmd_head, t_line *line)
{
	if (*cmd_head == NULL)
	{
		*cmd_head = (t_cmdlist *)malloc(sizeof(t_cmdlist));
		(*cmd_head)->line = line;
		(*cmd_head)->next = NULL;
		return;
	}

	t_cmdlist *current = *cmd_head;
	while (current->next != NULL)
		current = current->next;

	current->next = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	current->next->line = line;
	current->next->next = NULL;
}

void	parser(char **strs, t_cmdlist *cmd_head, t_rdlist *rd_head)
{
	int		i;
	t_line	line;

	i = 0;
	while (strs[i])
	{
		while (strs[i] && (i == 0 || strs[i][0] != '|'))
		{
			if (i == 0)
				line.pipe = 0;
			else
				line.pipe = 1;
			if (strs[i][0] == '<' || strs[i][0] == '>')
			{
				append_rd(&rd_head, strs[i], strs[i + 1]);
				i += 2;
			}
			else
			{
				j = 0;
				if
					// ft_strchr로 $ 찾으면
					// quote ??????어떻게 처리해야되지아너리ㅑ머ㅣ댜ㅜ라ㅓ루ㅡㄹ더ㅑ럼ㄷ니ㅏㅇㅋ.ㅣㅡㅋ타ㅓ얃ㅈ
				else
					// ft_strchr로 $ 못 찾으면
					// "\', \"" 구분자로 ft_strjoin -> line.cmd[j++] = strs[i];

				// 넣은만큼 i++;
			}
		}
		append_cmd(&cmd_head, line);
	}
}
*/

/*
int	main()
{
	char	**strs;
	t_cmdlist	*cmd_head = NULL;
	t_rdlist	*rd_head = NULL;

	char *str = (char *)malloc(50);
	str = "ls -al >> a.txt | env | grep PATH > b.txt > c.txt";
	strs = ft_split(str, ' ');

	// printf("*** split ***\n");
	// for (int i = 0; strs[i]; ++i)
	// 	printf("%s\n", strs[i]);
	// printf("\n");

	init_list(cmd_head, rd_head);
	parser(strs, cmd_head, rd_head);

	printf("*** cmdlist ***\n");
	print_cmdlist(cmd_head);
	printf("*** rdlist ***\n");
	print_rdlist(rd_head);

	// while ((*strs)++)
	// 	free(*strs);
	// free(strs);
	// free(str);
	return (0);
}
*/
