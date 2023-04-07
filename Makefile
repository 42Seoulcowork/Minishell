NAME = minishell

CC = cc

CFLAG = -Wall -Wextra -Werror -g -fsanitize=address

INC = -I./includes/

R_FLAG =  -lreadline #-L${HOME}/.brew/opt/readline/lib

RM = rm -f

#R_INC = -I${HOME}/.brew/opt/readline/include

LIB_FLAG = -Llib -lft

SRC =	main.c \
		execute/run_cmd.c \
		execute/env_node_utils.c \
		execute/env_node_utils2.c \
		execute/quick_sort.c \
		execute/execute.c \
		execute/execute_pipe.c \
		execute/handle_redir.c \
		execute/wrapper_sys_functions.c \
		execute/wrapper_lib_functions.c \
		execute/ft_split_s.c \
		built_in/ft_cd.c \
		built_in/ft_pwd.c \
		built_in/ft_exit.c \
		built_in/ft_echo.c \
		built_in/ft_env.c \
		built_in/ft_export.c \
		built_in/ft_export_utilis.c \
		built_in/ft_unset.c \
		parser/system_error.c \
#		parser/tokenize_func.c \
#		parser/parsing.c \
#		parser/tokenize_process_1st.c \
#		parser/tokenize_process_2nd.c \
#		parser/tokenize_process_3rd.c \
#		parser/tokenize_process_4th.c \
#		parser/tokenize_process_5th.c \
#		parser/error.c \
		# parser/queue.c \

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
