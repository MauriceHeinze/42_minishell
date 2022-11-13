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
	add_env(program->envp, "Maurice", "Schmidt");
	printf("env is %s\n", get_env(program->envp, "Maurice"));
	add_env(program->envp, "Maurice", "Heinze");
	printf("env is %s\n", get_env(program->envp, "Maurice"));
	return (0);
}