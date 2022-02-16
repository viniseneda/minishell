SRCS	= dict.c tokenizer.c list.c parser.c vars.c envp.c files.c minishell.c builtin_echo.c builtins.c builtin_exit.c builtin_cd_pwd.c
OBJS	= ${SRCS:.c=.o}

CC	= cc

CFLAGS =  #-Wall -Werror -Wextra

NAME	= minishell

.c.o:
	make -C ./libft all
	${CC} ${CFLAGS} -c ${SRCS}

RM	= rm -f

$(NAME):	${OBJS}
	cc -o $(NAME) ${OBJS} -L./libft -lft -lreadline -g


all:	$(NAME)

clean:
	${RM} ${OBJS}
	make -C ./libft clean

fclean:	clean
	${RM} ${NAME}
	make -C ./libft clean

re:	fclean all

.PHONY: 	all clean fclean
