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
		words[i] = NULL;
		free(words[i]);
		i++;
	}
	words = NULL;
	free(words);
}

int main(int argc, char *argv[], char *envp[])
{
	char	**words;
	char	*line;
	int		i;

	i = 0;
	// setup program
	program = malloc(sizeof(t_program));
	if (!program)
		return (0);
	program->envp = store_env(envp);
	add_env(program->envp, "Maurice", "Heinze");
	// printf("env is %s\n", get_env(program->envp, "Maurice"));
	// printf("env is %s\n", get_env(program->envp, "USER"));

	// printf("not_splitted is %s\n", program->envp->not_splitted);
	// start shell
	setup_term();
	while (1)
	{
		line = readline("minishell $");
		if (!line)
			break ;
		if (ft_strlen(line) == 0 || is_whitespace(line))
			continue ;
		track_history(line);
		line = expand_variables(line);
		words = split_line(line);
		words = split_subline(words);
		program->tokens = words;
		i = 0;
		program->cmd_line = line;
		program->nodes = fill_node(program);
		t_node *node = program->nodes;
		t_fd *fd = node->fd;
		// while (program->tokens[i] != NULL)
		// {
		// 	printf("%s\n", program->tokens[i]);
		// 	i++;
		// }
		execution_manager(node, program->envp);
		// write(1, "1 \n", 3);
		// printf("Full cmd: %s\n", node->full_cmd);
		// printf("Orig cmd: %s\n", node->full_cmd_orig);
		// printf("Full path: %s\n_____\n", node->full_path);
		// printf("Meta: %s\n_____\n", node->fd->meta);
		// while (node != NULL)
		// {
	// 	// 	node = node->next;
	// 	// 	// if (node)
	// 	// 	// 	fd = node->fd;
	// 	// }
	}
	return (0);
}

