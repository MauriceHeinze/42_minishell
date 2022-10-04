#include "../inc/minishell.h"

char	**ft_tokenizer(char *input_str)
{
	int		i;
	int		k;
	int		no_word;
	char	**words;

	words = malloc(sizeof(char *) * 10000);

	i = 0;
	k = 0;
	no_word = 0;
	while (no_word < 100)
	{
		words[no_word] = malloc(sizeof(char) * 100);
		no_word++;
	}
	no_word = 0;
	while (input_str[i] != '\0')
	{
		while (!ft_strchr("\'\" 	", input_str[i]) && input_str[i] != '\0')
		{
			if (input_str[i] == '\\')
			{
				i++;
				words[no_word][k++] = input_str[i++];
			}
			words[no_word][k++] = input_str[i++];
		}
		if (k > 0)
		{
			words[no_word++][k] = '\0';
			k = 0;
		}
		if (input_str[i] == '\'' || input_str[i] == '\"')
		{
			// printf("fire!\n");
			words[no_word] = copy_quote(input_str[i], input_str, i);
			i = i + ft_strlen(words[no_word++]);
			words[no_word - 1][ft_strlen(words[no_word - 1])] = input_str[i];
			// printf("\ntest: %c\n", input_str[i]);
			i++;
		}
		else if (ft_strchr(" 	", input_str[i]))
		{
			words[no_word][0] = input_str[i++];
			words[no_word++][1] = '\0';
		}
	}
	words[no_word] = NULL;
	return (words);
}