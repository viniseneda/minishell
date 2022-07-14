NAME	= minishell

CC	= cc

CFLAGS =  -Wall -Werror -Wextra

SRCS	= dict.c tokenizer.c list.c vars.c \
		parser_inout.c parse_pipe_hd.c parser_aux.c parser.c parser_nodes.c \
		envp.c files.c minishell.c builtin_echo.c builtins.c \
		builtin_exit.c builtin_cd_pwd.c tokenizer_aux1.c \
		 dict_env.c dict_setup.c execs.c \
		list_nodes.c list_free.c errors.c

OBJS	= ${SRCS:.c=.o}

.c.o:
	make -C ./libft all
	${CC} ${CFLAGS} -c ${SRCS}

RM	= rm -f

$(NAME):	${OBJS}
	$(CC) $(CFLAGS) -o $(NAME) ${OBJS} -g -L./libft -lft -lreadline


all:	$(NAME)

clean:
	${RM} ${OBJS}
	make -C ./libft clean

fclean:	clean
	${RM} ${NAME}
	make -C ./libft clean

re:	fclean all

.PHONY: 	all clean fclean
