#include "../inc/minishell.h"

t_program *program;

int main(int argc, char *argv[], char *envp[])
{
	// char	*input_str = "<Makefile cat| echo \"$PWD $e 'hola'\" ~/src | 'tr' -d / >outfile";
	char	*input_str = ">>";
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
	words = split_line(input_str);
	words = split_subline(words);
	program->tokens = words;

	// fill in nodes
	fill_node(program);
	// remove_quotes(words[i]);


	return (0);
}