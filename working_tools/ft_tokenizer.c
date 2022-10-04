#include "../inc/minishell.h"

// lexer -> expander ->  parser -> executor

// Todos
// - Rewrite ft_split to skip | if they are in quotes
// - Find out if you handle the input correctly now
// - maybe just start testing with prompt

char	*copy_quote(char found_quote, char *input_str, int pos)
{
	int		k;
	char	*quote;

	k = 0;
	quote = malloc(sizeof(char) * ft_strlen(input_str));
	// printf("Test: %c\n", input_str[pos]);
	quote[k++] = input_str[pos++];
	while (input_str[pos] != '\0')
	{
		if (input_str[pos] == found_quote)
			break ;
		else
		{
			if (input_str[pos] == '\\')
			{
				pos++;
				quote[k] = input_str[pos++];
			}
			else
				quote[k] = input_str[pos++];
			k++;
		}
	}
	quote[k] = '\0';
	return (quote);
}

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
	return (words);
}

int	main(int argc, char *argv[])
{
	char	**tokens;

	tokens = ft_tokenizer("Hallo \\\"Welt\" Test");
	printf("%s", tokens[0]);
	printf("%s", tokens[1]);
	printf("%s", tokens[2]);
	printf("%s", tokens[3]);
	printf("%s", tokens[4]);
	// printf("%s", tokens[5]);
	// printf("%s", tokens[6]);
	// printf("%s", tokens[7]);
	return (0);
}
