#include "../inc/minishell.h"

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

	// printf("\n=============\nstart! \n");
	i = 0;
	no_word = 0;
	start = 0;
	// printf("1\n");
	words = malloc(sizeof(char *) * get_total_words(splitted_line));
	// printf("total words %d\n", get_total_words(splitted_line));
	// printf("2\n");
	if (!words)
		return (NULL);
	// printf("3\n");
	while (splitted_line[i] != NULL)
	{
		if (count_words_operators(splitted_line[i]) == 1)
		{
			words[no_word] = splitted_line[i];
			no_word++;
		}
		else
		{
			k = 0;
			while (splitted_line[i][k] != '\0')
			{
				start = k;
				if (splitted_line[i][k] == '\"' || splitted_line[i][k] == '\'')
					k = skip_quote(splitted_line[i], k);
				while (!ft_strchr("|<>&", splitted_line[i][k]) && splitted_line[i][k] != '\0')
					k++;
				if (k > start)
				{
					words[no_word++] = ft_substr(splitted_line[i], start, k - start);
				}
				if (double_operator_found(splitted_line[i][k], splitted_line[i][k + 1]))
				{
					start = k;
					k += 2;
					// printf("k	%d\n", k);
					// printf("start	%d\n", start);
					words[no_word++] = ft_substr(splitted_line[i], start, k - start);
				}
				else if ((splitted_line[i][k] == '<') || (splitted_line[i][k]  == '>') || (splitted_line[i][k]  == '|'))
				{
					start = k;
					k++;
					words[no_word++] = ft_substr(splitted_line[i], start, k - start);
					if (splitted_line[i][k] == ' ')
						k++;

				}
				else
					k++;
			}
		}
		i++;
	}
	// printf("end! \n");
	words[get_total_words(splitted_line) - 1] = NULL;
	free_split(splitted_line);

	i = 0;
	while (splitted_line[i] != NULL)
	{
		// printf("%s \n", splitted_line[i]);
		i++;
	}
	return (words);
}