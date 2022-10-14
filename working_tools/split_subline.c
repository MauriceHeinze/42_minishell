#include "../inc/minishell.h"

static int	double_operator_found(char a, char b)
{
	if (a == '<' && b == '<')
		return (1);
	else if (a == '>' && b == '>')
		return (1);
	else if (a == '&' && b == '&')
		return (1);
	else if (a == '|' && b == '|')
		return (1);
	return (0);
}

static int	get_total_words(char **splitted_line)
{
	int		i;
	int		total_words;

	i = 0;
	total_words = 1;
	while (splitted_line[i] != NULL)
	{
		total_words += count_words_operators(splitted_line[i]);
		i++;
	}
	return (total_words);
}

char	**split_subline(char **splitted_line)
{
	int		i;
	int		k;
	int		start;
	int		no_word;
	char	**words;

	i = 0;
	no_word = 0;
	start = 0;
	words = malloc(sizeof(char *) * get_total_words(splitted_line));
	if (!words)
		return (NULL);
	while (splitted_line[i] != NULL)
	{
		if (count_words_operators(splitted_line[i]) == 1)
			words[no_word++] = splitted_line[i];
		else
		{
			k = 0;
			while (splitted_line[i][k] != '\0')
			{
				start = k;
				while (!ft_strchr("|<>&", splitted_line[i][k]) && splitted_line[i][k] != '\0')
					k++;
				if (k > start)
					words[no_word++] = ft_substr_backslash(splitted_line[i], start, k - start);
				if (double_operator_found(splitted_line[i][k], splitted_line[i][k + 1]))
				{
					start = k;
					k += 2;
					// printf("k	%d\n", k);
					// printf("start	%d\n", start);
					words[no_word++] = ft_substr_backslash(splitted_line[i], start, k - start);
				}
				else if ((splitted_line[i][k]  == '<') || (splitted_line[i][k]  == '>') || (splitted_line[i][k]  == '|'))
				{
					start = k;
					k++;
					words[no_word++] = ft_substr_backslash(splitted_line[i], start, k - start);
				}
				else
					k++;
			}
		}
		i++;
	}

	words[get_total_words(splitted_line) - 1] = NULL;
	return (words);
}