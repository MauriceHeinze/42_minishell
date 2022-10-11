#include "../inc/minishell.h"

char	**split_line(char *input_str)
{
	int		i;
	int		k;
	int		no_word;
	char	**words;
	int		total_words;

	total_words =  count_words(input_str) + 1;

	words = malloc(sizeof(char *) * total_words);
	words = ft_calloc(total_words, sizeof(char *));

	i = 0;
	k = 0;
	no_word = 0;
	while (no_word <  (count_words(input_str) + 1))
	{
		words[no_word] = malloc(sizeof(char) * 100);
		no_word++;
	}
	no_word = 0;
	while (input_str[i] != '\0')
	{
		// printf("Run %d\n", i);
		while (!ft_strchr("\'\" 	", input_str[i]) && input_str[i] != '\0')
		{
			if (input_str[i] == '\\')
			{
				i++;
				words[no_word][k++] = input_str[i++];
			}
			words[no_word][k++] = input_str[i++];
		}
		// printf("%s  - Index: %d \n", words[no_word], no_word);
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
		else
			i++;
	}
	printf("First word in split_line: %s\n", words[0]);
	// printf("%d\n", count_words(input_str));
	words[total_words - 1] = NULL;
	return (words);
}