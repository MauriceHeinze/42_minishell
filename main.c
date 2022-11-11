#include "./inc/minishell.h"

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
	// printf("Paths are %s\n", get_cmd_paths(program->envp)[0]);
	// start shell
	setup_signal_handler();
	while (1)
	{
		line = readline("minishell $");
		if (ft_strlen(line) == 0)
			continue ;
		track_history(line);
		line = expand_variables(line);
		words = split_line(line);
		words = split_subline(words);
		program->tokens = words;
		program->cmd_line = line;
		program->nodes = fill_node(program);
		t_node *node = program->nodes;
		t_fd *fd = node->fd;
		// printf("Mode: %s\n", node->full_cmd);
		// printf("Meta: %s\n_____\n", node->full_path);
		// while (node != NULL)
		// {
		// 	// EXECUTOR COMMAND HIER EINFÜGEN
		// 	node = node->next;
		// 	// if (node)
		// 	// 	fd = node->fd;
		// }

		// free(program->tokens);
		// free(program->cmd_line);
		// free(program->cmd_line);
		// free_nodes(program);
		// free(program);
		// free(node);
		// free(fd);
		// free_split(words);
		// free(line);
	}
	return (0);
}