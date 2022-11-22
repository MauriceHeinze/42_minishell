CLIENT_NAME = minishell
SOURCES = 	./env/store_env.c							\
			./exec/builtins.c							\
			./exec/executor.c							\
			./exit/error_message.c						\
			./exit/exit_shell.c							\
			./linked_list/fill_fd.c						\
			./linked_list/fill_node.c					\
			./linked_list/free_nodes.c					\
			./parser/check_syntax.c						\
			./parser/expand_variable.c					\
			./parser/split_line.c						\
			./parser/split_subline.c					\
			./parser_helper/count_words.c				\
			./parser_helper/get_category.c				\
			./parser_helper/quotes.c					\
			./parser_helper/str_add.c					\
			./parser_helper/str_remove.c				\
			./readline_helper/is_whitespace.c			\
			./readline_helper/track_history.c			\
			./utils/count_operators.c					\
			./utils/get_cmd_path.c						\
			./utils/remove_quotes.c						\
			./utils/signal_handler.c					\
			./inc/libft.a 								\

CLIENT = main.c $(SOURCES)

CLIENTOBJ =	$(CLIENT:.c=.o)

HDR = ./inc/minishell.h
CC = cc -g
# FLAGS = -Wall -Wextra -Werror -lreadline -L /opt/homebrew/Cellar/readline/8.2.1/lib -I /opt/homebrew/Cellar/readline/8.2.1/include/
FLAGS = -Wall -Wextra -Werror -lreadline -L ./readline/ -lhistory -L ./readline/ -I /readline/ -ltermcap
RM = rm -f

all: $(CLIENT_NAME)
$(CLIENT_NAME): $(HDR) $(CLIENTOBJ)
	$(CC) $(FLAGS) $(CLIENTOBJ) -o $(CLIENT_NAME)

clean:
	$(RM) *.o
	$(RM) */*.o
	$(RM) *.out

fclean: clean
	$(RM) $(CLIENT_NAME)

re:	fclean all

.PHONY: all clean fclean