#include "../inc/minishell.h"

int	main(int argc, char *argv[])
{
	char	*line;

	// prompt = readline("USER@MINISHELL:");
	// add_history(prompt);
	// printf("%s\n", prompt);
	// printf("test %s\n", readline("USER@MINISHELL:"));


	while (1)
	{
		line = readline("\e[1;92mminishell\e[1;94m $\e[0;37m ");
		if (line[0] != '\0')
			add_history(line);
		printf("%s\n", line);
		free(line);
	}
	// add_history("test");
	return (0);
}