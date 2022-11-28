#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libft/libft.h"


void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

int main(int argc, char *argv[], char *envp[])
{
	char	**word = ft_split("hello world", ' ');

	printf("%s\n", word[0]);
	printf("%s\n", word[1]);
	free_split(word);
	printf("%s\n", word[0]);
	printf("%s\n", word[1]);

	return (0);
}
