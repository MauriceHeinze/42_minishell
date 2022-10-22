#include "../inc/minishell.h"

t_program *program;

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
	char	*input_str = "<Makefile cat| echo \"$PWD $e 'hola'\" ~/src | 'tr' -d / >outfile";
	// char	*input_str = "echo 'Current Path is: ' $PWD | echo 'User name is: ' $USER | cat";
	// char	*input_str = "< infile ls -l | wc -l > outfile";
	// char	*input_str = "echo -n 'Max' > output1 > output2 | cat 'Paul' > 4k | cd 'Maurice' > hdmi > xyz | pwd 'Marie' > abc > 123";
	// char	*input_str = "< infile.txt echo 'Hallo' > output1 > output2 > output3";
	char	**words;
	int		i;

	i = 0;
	// setup program
	program = malloc(sizeof(t_program));
	if (!program)
		return (0);
	program->envp = envp;
	input_str = expand_variables(input_str);
	// printf("%s \n", input_str);
	words = split_line(input_str);
	words = split_subline(words);
	// while (words[i] != NULL)
	// {
	// 	printf("%s \n", words[i]);
	// 	i++;
	// }
	program->tokens = words;
	program->cmd_line = input_str;
	i = 0;
	program->nodes = fill_node(program);
	t_node *node = program->nodes;
	t_fd *fd = node->fd;
	while (node != NULL)
	{
		printf("Command:	%s \n", node->full_cmd);
		printf("Path:		%s \n", node->full_path);
		printf("-- FD ---------------\n");
		while (fd != NULL)
		{
			printf("IO:	%d \n", fd->io);
			printf("Mode:	%d \n", fd->mode);
			printf("Meta:	%s \n", fd->meta);
			printf("- - - - - - - - - - -\n");
			fd = fd->next;
		}

		node = node->next;
		if (node)
			fd = node->fd;
	}
	// free(program->envp);
	// free_split(words);
	// system("leaks a.out");
	return (0);
}