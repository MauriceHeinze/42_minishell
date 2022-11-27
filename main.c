#include "./inc/minishell.h"
#include "./exec/executor.h"

static void setup_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
	setup_signal_handler();
}

static void	free_program_loop()
{
	int		i;

	t_node	*node;
	i = 0;
	// free(program->cmd_line);
	free_split(program->tokens);
	// node = program->nodes;
	free_nodes(program);
}

int main(int argc, char *argv[], char *envp[])
{
	char	**words;
	char	**subwords;
	char	*line;
	int		i;

	i = 0;
	// setup program
	program = malloc(sizeof(t_program));
	if (!program)
		return (0);
	program->envp = store_env(envp);
	set_exit_code(0);
	setup_term();
	// while (1)
	// {
		line = readline("minishell $");
		// if (!line)
		// 	break ;
		// if (ft_strlen(line) == 0 || is_whitespace(line))
		// 	continue ;
		track_history(line);
		line = expand_variables(line);
		words = split_line(line);
		// i = 0;
		// while (words[i])
		// {
		// 	printf("%s \n", words[i]);
		// 	i++;
		// }
		subwords = split_subline(words);
		// exit(1);
		// if (!check_syntax(program->tokens))
		// 	continue ;
		program->tokens = subwords;
		program->cmd_line = line;
		program->nodes = fill_node(program);
		t_node *node = program->nodes;
		t_fd *fd = node->fd;
		execution_manager(node, program->envp);
		// free_program_loop();
		printf("-------------->\n");
		while (node != NULL)
		{
			printf("\nFull cmd: %s\n", node->full_cmd);
			printf("Orig cmd: %s\n", node->full_cmd_orig);
			node = node->next;
		}
	// }
	return (0);
}

