#include "../inc/minishell.h"

// lexer -> expander ->  parser -> executor

// Todos
// - handle special chars like /t /n etc.
// - recognize commands like >> && || etc.

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
	words[no_word] = NULL;
	return (words);
}

int		is_command(char *word)
{
	// printf("result:	%d\n", ft_strcmp(word, "echo"));
	if (ft_strcmp(word, "echo") == 0)
		return (ECHO);
	if (ft_strcmp(word, "cd") == 0)
		return (CD);
	if (ft_strcmp(word, "pwd") == 0)
		return (PWD);
	if (ft_strcmp(word, "export") == 0)
		return (EXPORT);
	if (ft_strcmp(word, "unset") == 0)
		return (UNSET);
	if (ft_strcmp(word, "env") == 0)
		return (ENV);
	if (ft_strcmp(word, "exit") == 0)
		return (EXIT);
	return (0);
}

int		is_operator(char *word)
{
	if (ft_strcmp(word, ">") == 0)
		return (ARROW_LEFT);
	if (ft_strcmp(word, ">>") == 0)
		return (DOUBLE_ARROW_LEFT);
	if (ft_strcmp(word, "<") == 0)
		return (ARROW_RIGHT);
	if (ft_strcmp(word, "<<") == 0)
		return (DOUBLE_ARROW_RIGHT);
	if (ft_strcmp(word, "|") == 0)
		return (PIPE);
	if (ft_strcmp(word, "||") == 0)
		return (OR);
	if (ft_strcmp(word, "&&") == 0)
		return (AND);
	if (word == NULL)
		return (EXIT);
	return (0);
}

int		get_category(char *word)
{
	// printf("result:	%d\n", ft_strcmp(word, "echo"));
	if (is_command(word) > 0)
		return (is_command(word));
	else if (is_operator(word) > 0)
		return (is_operator(word));
	else if ((ft_strcmp(word, " ") == 0) || (ft_strcmp(word, "	") == 0))
		return (WHITE_SPACE);
	else if (ft_strcmp(word, "\'") == 0)
		return (QUOTE);
	else if (ft_strcmp(word, "\"") == 0)
		return (DOUBLE_QUOTE);
	else
		return (WORD);
	return (0);
}

int	main(int argc, char *argv[])
{
	char	**tokens;
	int		i;

	i = 0;
	// printf("Test %d\n", is_command("echo"));
	tokens = ft_tokenizer("cd ../Desktop | echo \"Hallo Welt!\" >> file.txt");

	while (tokens[i] != NULL)
	{
		// printf("%s\n", tokens[i]);
		// if (is_command(tokens[i]))
		// 	printf("%s is %d\n", tokens[i], is_command(tokens[i]));
		// if (is_operator(tokens[i]))
		// 	printf("%s is %d\n", tokens[i], is_operator(tokens[i]));
		printf("%s is %d\n", tokens[i], get_category(tokens[i]));
		i++;
	}

	return (0);
}
