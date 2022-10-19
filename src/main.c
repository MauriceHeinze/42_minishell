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
	char	**words;
	int		i;

	i = 0;
	// setup program
	program = malloc(sizeof(t_program));
	if (!program)
		return (0);
	program->envp = envp;
	// work on input
	// printf("%s \n", input_str);
	input_str = expand_variables(input_str);
	words = split_line(input_str);
	// printf("1: %s \n", words[0]);
	words = split_subline(words);
	while (words[i] != NULL)
	{
		i++;
	}
	printf("total_words: %d\n", i);
	program->tokens = words;
	i = 0;
	while (words[i] != NULL)
	{
		printf("%s \n", words[i]);
		i++;
	}

	program->nodes = fill_node(program);
	t_node *node = program->nodes;
	while (node != NULL)
	{
		printf("%d	Command:	%s \n", i++, node->full_cmd);
		printf("%d:	Path:		%s \n", i++, node->full_path);
		printf("%d:	Mode:		%d \n", i++, node->infile_mode);
		printf("%d:	Meta:		%s \n", i++, node->infile_meta);
		printf("-----------\n");
		node = node->next;
	}
	free(program);
	free_split(words);
	return (0);
}