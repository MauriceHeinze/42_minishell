#include "../inc/minishell.h"

char	**split_line(char *input_str)
{
	int		i;
	int		start;
	int		no_word;
	int		total_words;
	char	**words;

	i = 0;
	start = 0;
	no_word = 0;
	total_words = count_words(input_str) + 1;
	words = malloc(sizeof(char *) * total_words);
	if (!words)
		return (NULL);
	while (input_str[i] != '\0')
	{
		start = i;
		while (!ft_strchr("\'\" 	", input_str[i]) && input_str[i] != '\0')
		{
			if (input_str[i] == '\\')
				i = i + 2;
			else
				i++;
		}
		if (i > start)
			words[no_word++] = ft_substr_backslash(input_str, start, i - start);
		if (input_str[i] == '\'' || input_str[i] == '\"')
		{
			i = i + quote_length(input_str[i], input_str, i) + 1;
			words[no_word++] = ft_substr_backslash(input_str, start, i - start + 1);
			i++;
		}
		else
			i++;
	}
	words[total_words - 1] = NULL;
	return (words);
}