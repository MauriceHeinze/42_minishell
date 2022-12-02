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
		if (isatty(STDIN_FILENO))
			line = readline("minishell $");
		else
			line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strlen(line) == 0 || is_whitespace(line))
			continue ;
		track_history(line);
		expanded_line = expand_variables(line);
		words = split_line(expanded_line);
		subwords = split_subline(words);
		// i = 0;
		// while (words[i])
		// {
		// 	printf("%s \n", words[i]);
		// 	i++;
		// }
		if (!check_syntax(subwords))
			continue ;
		program->tokens = subwords;
		i = 0;
		while (program->tokens[i])
		{
			i++;
		}
		program->nodes = fill_node(program);
		if (program->nodes == NULL)
		{
			printf("minishell: %s: command not found\n", program->tokens[0]);
			free_split(program->tokens);
			free_split(words);
			// system("leaks minishell");
			continue;
		}
		execution_manager(program->nodes, program->envp);
		free_split(words); // results in double free
		words = NULL;
		// free_split(subwords);
		// free(expanded_line); // frees twice somehow, Linux dislikes it
		// printf("==========>\n");
		// printf("1 ==========>\n");
		// printf("--------TEST--------->\n");
		// t_node *node = program->nodes;
		// t_fd *fd = node->fd;
		// while (node != NULL)
		// {
		// 	printf("\nFull cmd: %s|\n", node->full_cmd);
		// 	printf("Orig cmd: %s|\n", node->full_cmd_orig);
		// 	node = node->next;
		// }
		// free(expanded_line);
		// expanded_line = NULL;
		free_program_loop();
		// free(line);
		// printf("exp: %s\n", expanded_line);
		// expanded_line = NULL;
		// system("leaks minishell");
	}
	free_env();
	// system("leaks minishell");
	return (0);
}

// echo hallo > file.txt