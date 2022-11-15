CLIENT_NAME = minishell
SOURCES = 	./working_tools/copy_quote.c				\
			./executor/get_cmd_path.c					\
			./exec/executor.c							\
			./exec/builtins.c							\
			./working_tools/count_operators.c			\
			./working_tools/count_words.c				\
			./working_tools/expand_variable.c			\
			./working_tools/fill_fd.c					\
			./working_tools/fill_node.c					\
			./working_tools/ft_substr_backslash.c		\
			./working_tools/ft_tokenizer.c				\
			./working_tools/get_category.c				\
			./working_tools/quote_length.c				\
			./working_tools/remove_quotes.c				\
			./working_tools/skip_quote.c				\
			./working_tools/special_char.c				\
			./working_tools/split_line.c				\
			./working_tools/split_subline.c				\
			./working_tools/store_env.c					\
			./working_tools/str_add.c					\
			./working_tools/str_remove_word.c			\
			./working_tools/track_history.c				\
			./working_tools/signal_handler.c			\
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