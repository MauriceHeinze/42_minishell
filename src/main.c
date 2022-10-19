#include "../inc/minishell.h"

t_program *program;

int main(int argc, char *argv[], char *envp[])
{
	// char	*input_str = "<Makefile cat| echo \"$PWD $e 'hola'\" ~/src | 'tr' -d / >outfile";
	char	*input_str = "echo 'Current Path is: ' $PWD | echo 'User name is: ' $USER | cat";
	// char	*input_str = "< infile grep a1 | wc -w > outfile";
	char	**words;
	int		i;

	i = 0;
	// setup program
	program = malloc(sizeof(t_program *));
	if (!program)
		return (0);
	program->envp = envp;
	program->cmd_line = input_str;


	// work on input
	input_str = expand_variables(input_str);
	// printf("%s \n", input_str);
	words = split_line(input_str);
	words = split_subline(words);
	program->tokens = words;

	// while (words[i] != NULL)
	// {
	// 	printf("%s \n", words[i]);
	// 	i++;
	// }

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
	return (0);
}