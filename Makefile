CLIENT_NAME = minishell
SOURCES = 	./working_tools/copy_quote.c				\
			./executor/get_cmd_path.c					\
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
			./working_tools/str_add.c					\
			./working_tools/str_remove_word.c			\
			./working_tools/free_nodes.c			\

CLIENT = main.c $(SOURCES)

CLIENTOBJ =	$(CLIENT:.c=.o)

HDR = ./inc/minishell.h
CC = cc
FLAGS = -g -Wall -Wextra -Werror
RM = rm -f

all: $(CLIENT_NAME)
$(CLIENT_NAME): $(HDR) $(CLIENTOBJ)
	$(MAKE) -C libft
	$(CC) $(FLAGS) $(CLIENTOBJ) ./libft/libft.a -o $(CLIENT_NAME)

clean:
	$(RM) *.o
	$(RM) */*.o
	$(RM) *.out

fclean: clean
	$(RM) $(CLIENT_NAME)

re:	fclean all

.PHONY: all clean fclean