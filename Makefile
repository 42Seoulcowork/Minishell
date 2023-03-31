NAME = minishell

CC = cc

CFLAG = -Wall -Wextra -Werror -g

INC = -I./includes/

R_FLAG =  -lreadline #-L${HOME}/.brew/opt/readline/lib

RM = rm -f

#R_INC = -I${HOME}/.brew/opt/readline/include

LIB_FLAG = -Llib -lft
# > ${HOME} 환경변수를 이용해서 경로 부분이 자동으로 치환되게끔 하자.
# > brew로 readline을 설치한 맥이라면 어디서든 경로를 잘 찾을 수 있을 것이다.

SRC =	main.c \
		execute/envp_init.c \
		execute/run_cmd.c \
		execute/pipe_run.c \
		execute/pipe_pid.c \
		execute/pipe_utils.c \
		execute/pipe_error.c \
		execute/pipe_split_set.c \
		execute/env_node_utils.c \
		execute/quick_sort.c \
		built_in/ft_cd.c \
		built_in/ft_pwd.c \
		built_in/ft_exit.c \
		built_in/ft_echo.c \
		built_in/ft_env.c \
		built_in/ft_export.c \
		built_in/ft_unset.c \
#		parser/tokenize.c \
#		parser/token_utils.c \
#		parser/parsing.c \
#		parser/queue.c \

SRC_DIR = ./srcs/

OBJS = $(SRCS:.c=.o)
SRCS = $(addprefix $(SRC_DIR), $(SRC))


all : $(NAME)

.c.o:
	@$(CC) $(CFLAG) $(INC) $(R_INC) -c $< -o $@

$(NAME): $(OBJS)
	@make -C lib
	@$(CC) $(CFLAG) $^ $(LIB_FLAG) $(R_FLAG) -o $@ #buntu는 object 파일이 라이브러리보다 앞에 있어야 한다.
	@printf	"Get Ready for the Minishell\n"

clean :
	@make clean -C lib
	@$(RM) $(OBJS)
	@printf	"Run to Clean\n"

fclean :
	@make clean -C lib
	@$(RM) $(OBJS)
	@$(RM) $(NAME)
	@printf	"Run to fClean\n"

re : fclean all

.PHONY : all clean fclean re
