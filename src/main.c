#include "../inc/minishell.h"

// lexer -> expander ->  parser -> executor

// Todos
// - handle special chars like /t /n etc.
// - recognize commands like >> && || etc.

int	main(int argc, char *argv[])
{
	char	**tokens;
	int		i;

	i = 0;
	// printf("Test %d\n", is_command("echo"));
	tokens = ft_tokenizer("cd ../Desktop | echo \"Hallo Welt!\" >> file.txt");

	while (tokens[i] != NULL)
	{
		// printf("%s is %d\n", tokens[i], get_category(tokens[i]));
		printf("%s", tokens[i]);
		i++;
	}
	return (0);
}
