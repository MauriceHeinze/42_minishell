#include "../inc/minishell.h"

// TODO
// - leaks are generated by not handling quote errors correctly
// example:	char	*input_str = "< infile ls -l | wc -l > outfile'";

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
	total_words = count_words(input_str);
	words = malloc(sizeof(char *) * (total_words + 1));
	if (!words)
		return (NULL);
	while (input_str[i] != '\0')
	{
		start = i;
		while (!ft_strchr("\'\" 	", input_str[i]) && input_str[i] != '\0')
			i++;
		if (i > start)
		{
			words[no_word++] = ft_substr(input_str, start, i - start);
			continue;
		}
		if (input_str[i] == '\'' || input_str[i] == '\"')
		{
			i = i + quote_length(input_str[i], input_str, i) + 1;
			words[no_word++] = ft_substr(input_str, start, i - start + 1);
			i++;
		}
		i++;
	}
	printf("total_words: %s\n", words[total_words]);
	words[total_words + 1] = NULL;
	system("leaks a.out");
	return (words);
}