#include "../inc/minishell.h"

char	**split_line(char *input_str)
{
	int		i;
	int		k;
	int		no_word;
	char	**words;

	words = malloc(sizeof(char *) * (count_words(input_str)));
	words = ft_calloc(count_words(input_str) + 1, sizeof(char *));

	i = 0;
	k = 0;
	no_word = 0;
	while (no_word < 100)
	{
		words[no_word] = malloc(sizeof(char) * 100);
		words[no_word][0] = '\0';
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
	// printf("Last word:	%s\n", words[no_word - 3]);
	// printf("no_word:	%d\n", no_word);

	// printf("char:	%d\n", words[no_word - 1][0]);
	// printf("char:	%d\n", words[no_word - 2][0]);
	// printf("char:	%d\n", words[no_word - 3][0]);
	// printf("char:	%d\n", words[no_word - 4][0]);
	// words[no_word - 4] = NULL;
	return (words);
}