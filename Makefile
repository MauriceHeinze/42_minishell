NAME = minishell
SOURCES = 	./env/add_env.c							\
			./env/store_env.c						\
			./env/store_env_s.c						\
			./env/remove_env.c						\
			./env/setup_fd.c						\
			./executor/executor.c					\
			./executor/executor_init.c				\
			./executor/executor_heredoc.c			\
			./executor/executor_fd_manager.c		\
			./executor/executor_funct.c				\
			./executor/executor_utils.c				\
			./executor/builtins.c					\
			./executor/builtins_funct.c				\
			./executor/builtins_extra.c				\
			./executor/builtins_utils.c				\
			./executor/builtins_cd.c				\
			./linked_list/fill_fd.c					\
			./linked_list/fill_node.c				\
			./linked_list/fill_node_helper.c		\
			./linked_list/free_nodes.c				\
			./linked_list/free.c					\
			./parser/check_syntax.c					\
			./parser/expand_variable.c				\
			./parser/split_line.c					\
			./parser/split_line_counter.c			\
			./parser/split_subline.c				\
			./parser_helper/get_category.c			\
			./parser_helper/quotes.c				\
			./parser_helper/split_subline_helper.c	\
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
			./utils/check_line.c					\
			./get_next_line/get_next_line_utils.c	\
			./get_next_line/get_next_line.c

CLIENT = main.c $(SOURCES)

CLIENTOBJ =	$(CLIENT:.c=.o)

HOMEPATH = ${HOME}
HDR = ./inc/minishell.h
CC = cc -g -Wall -Wextra -Werror
CFLAGSMAC = -lreadline -L ./readline/ -lhistory -L ./readline/ -I /readline/ -ltermcap
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