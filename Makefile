NAME = minishell

CC = cc

CFLAG = -Wall -Wextra -Werror

RFLAG =  -lreadline -L${HOME}/.brew/opt/readline/lib

INC = -I${HOME}/.brew/opt/readline/include
# > ${HOME} 환경변수를 이용해서 경로 부분이 자동으로 치환되게끔 하자.
# > brew로 readline을 설치한 맥이라면 어디서든 경로를 잘 찾을 수 있을 것이다.

SRCS = \
	main.c \

OBJS = $(SRCS:.c=.o)

OBJ_DIR := obj

OBJS_FILES := $(addprefix $(OBJ_DIR)/, $(OBJS))

all : $(NAME)

$(NAME): $(OBJS_FILES)
	@$(CC) $(CFLAG) $^ -o $@ $(RFLAG)
	@printf	"Get Ready for the Minishell\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	@$(CC) $(CFLAG) $(INC) -c $< -o $@ 

clean :
	@rm -rf $(OBJ_DIR)
	@printf	"Run to Clean\n"

fclean :
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@printf	"Run to fClean\n"

re : fclean all

.PHONY : all clean fclean re
