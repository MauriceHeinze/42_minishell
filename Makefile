NAME = minishell
SOURCES = 	./env/add_env.c							\
			./env/store_env.c						\
			./env/remove_env.c						\
			./env/setup_fd.c						\
			./exec/builtins.c						\
			./exec/executor.c						\
			./linked_list/fill_fd.c					\
			./linked_list/fill_node.c				\
			./linked_list/free_nodes.c				\
			./linked_list/free.c					\
			./parser/check_syntax.c					\
			./parser/expand_variable.c				\
			./parser/split_line.c					\
			./parser/split_line_counter.c			\
			./parser/split_subline.c				\
			./parser_helper/get_category.c			\
			./parser_helper/quotes.c				\
			./parser_helper/str_add.c				\
			./parser_helper/str_remove.c			\
			./utils/count_operators.c				\
			./utils/env_handler.c					\
			./utils/exit_handler.c					\
			./utils/fd_handle_redirections.c		\
			./utils/get_cmd_path.c					\
			./utils/init_to_zero.c					\
			./utils/signal_handler.c				\
			./utils/track_history.c					\
			./get_next_line/get_next_line_utils.c	\
			./get_next_line/get_next_line.c

CLIENT = main.c $(SOURCES)

CLIENTOBJ =	$(CLIENT:.c=.o)

HDR = ./inc/minishell.h ./get_next_line/get_next_line.h
CC = cc -g
# FLAGS = -Wall -Wextra -Werror -lreadline -L /opt/homebrew/Cellar/readline/8.2.1/lib -I /opt/homebrew/Cellar/readline/8.2.1/include/
CFLAGSMAC = -Wall -Wextra -Werror -lreadline -L ./readline/ -lhistory -L ./readline/ -I /readline/ -ltermcap
CFLAGSLINUX = -lreadline
RM = rm -f

all: $(NAME)

$(NAME): $(HDR) $(CLIENTOBJ)
	make -C ./libft
	$(CC) $(CFLAGSMAC) $(CLIENTOBJ) ./libft/libft.a -o $(NAME)

allLinux: nameLinux

nameLinux: $(HDR) $(CLIENTOBJ)
	make -C ./libft
	$(CC) $(CLIENTOBJ) ./libft/libft.a $(CFLAGSLINUX) -o $(NAME)

clean:
	make fclean -C ./libft
	$(RM) *.o
	$(RM) */*.o
	$(RM) *.out

fclean: clean
	$(RM) $(NAME)

re:	fclean all

rel: fclean allLinux

.PHONY: all clean fclean