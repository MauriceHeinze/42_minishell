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
	free_split(program->tokens);
	free_nodes(); // not working with linux
}

int main(int argc, char *argv[], char *envp[])
{
	char	**words;
	char	**subwords;
	char	*line;
	char	*expanded_line;
	int		i;

	i = 0;
	// setup program
	program = malloc(sizeof(t_program));
	if (!program)
		return (0);
	program->envp = store_env(envp);
	set_exit_code(0);
	setup_term();
	while (1)
	{
		line = readline("minishell $");
		if (!line)
			break ;
		if (ft_strlen(line) == 0 || is_whitespace(line))
			continue ;
		track_history(line);
		expanded_line = expand_variables(line);
		words = split_line(expanded_line);
		subwords = split_subline(words);
		if (!check_syntax(subwords))
			continue ;
		program->tokens = subwords;
		program->nodes = fill_node(program);
		execution_manager(program->nodes, program->envp);
		free_split(words); // results in double free
		words = NULL;
		subwords = NULL;
		i = 0;
		while (program->tokens[i])
		{
			printf("%s \n", program->tokens[i]);
			i++;
		}
		// free_split(subwords);
		// free(expanded_line); // frees twice somehow, Linux dislikes it
		free(line);
		// printf("1 ==========>\n");
		// printf("--------TEST--------->\n");
		// t_node *node = program->nodes;
		// t_fd *fd = node->fd;
		// while (node != NULL)
		// {
		// 	printf("\nFull cmd: %s\n", node->full_cmd);
		// 	printf("Orig cmd: %s\n", node->full_cmd_orig);
		// 	node = node->next;
		// }
		// printf("2 ==========>\n");
		free_program_loop();
		system("leaks minishell");
	}
	free_env();
	return (0);
}

