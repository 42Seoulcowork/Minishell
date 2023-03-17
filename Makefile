NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $< -o $@ -lreadline
	@printf	"Get Ready for the Minishell\n"

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean :
	@rm -f $(OBJS)
	@printf	"Run to Clean\n"

fclean :
	@rm -f $(OBJS)
	@rm -f $(NAME)
	@printf	"Run to fClean\n"

re : fclean all

.PHONY : all clean fclean re
