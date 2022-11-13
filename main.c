#include "./inc/minishell.h"
#include "./exec/executor.h"

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
	setup_signal_handler();
	while (1)
	{
		line = readline("minishell $");
		if (!line)
			break ;
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
		execution_manager (node, program->envp);
		printf("Full cmd: %s\n", node->full_cmd);
		printf("Full path: %s\n_____\n", node->full_path);
		printf("Meta: %s\n_____\n", node->fd->meta);
		// while (node != NULL)
		// {
	// 	// 	node = node->next;
	// 	// 	// if (node)
	// 	// 	// 	fd = node->fd;
	// 	// }
	}
	return (0);
}