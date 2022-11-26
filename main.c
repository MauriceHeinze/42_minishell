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

static void	free_split(char **words)
{
	int	i;

	if (words == NULL)
		return ;
	i = 0;
	while (words[i] != NULL)
	{
		free(words[i]);
		words[i] = NULL;
		i++;
	}
	free(words);
	words = NULL;
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
		subwords = split_subline(words);
		// i = 0;
		// while (subwords[i])
		// {
		// 	printf("%s \n", subwords[i]);
		// 	i++;
		// }
		// free_split(words);
		// exit(1);
		// if (!check_syntax(program->tokens))
		// 	continue ;
		program->tokens = subwords;
		program->cmd_line = line;
		program->nodes = fill_node(program);
		t_node *node = program->nodes;
		t_fd *fd = node->fd;
		execution_manager(node, program->envp);
		free_split(program->tokens);
		// while (node != NULL)
		// {
		// 	printf("\n\nFull cmd: %s\n", node->full_cmd);
		// 	printf("Orig cmd: %s\n", node->full_cmd_orig);
		// 	node = node->next;
		// }
	// }
	return (0);
}

