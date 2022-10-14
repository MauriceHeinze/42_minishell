#include "../inc/minishell.h"

int	main(int argc, char *argv[])
{
	// char		*input_str = " 	   	cd ../Desktop | echo \"Hallo Welt!\" >> file.txt 	 	 ";
	// char		*input_str = " 	   	cd ../Desktop | touch file_21.txt | echo \"Hallo Welt!\" >> file.txt 	 	 ";
	// char	*input_str = "echo               text \"$USER\"            \"$USER\"text";
	char	*input_str = "<Makefile cat| echo \"$PWD 'hola'\" ~/src | 'tr' -d / >outfile";
	// char	*input_str = "aaa>bbb>ccc&&ddd>>";

	char		**words;
	t_token		*tokens;
	int			i;

	i = 0;

	// tokens = malloc(sizeof(tokens));

	// printf("Test %d\n", is_command("echo"));

	input_str = ft_strtrim(input_str, " 	");
	words = split_line(input_str);
	words = split_subline(words);
	while (words[i] != NULL)
	{
		words[i] = remove_quotes(words[i]);
		printf("%s\n", words[i]);
		i++;
	}
	// printf("First word in main: %s\n", words[0]);
	// tokens = tokenizer(words);
	// printf("Result: %s\n", ft_substr_backslash(input_str, 0, 100));

	// printf("%s\n", words[14]);
	// words[14] = NULL;

	// int i = 0;
	// while (words[i] != NULL)
	// 	printf("%s\n", words[i++]);
	// printf("%s", tokens->word);
	// tokens = tokens->next;
	// printf("%s", tokens->word);

	// printf("spaces: %d\n", count_spaces("cd ../Desktop | echo \"Hallo Welt!\" >> file.txt"));

	// printf("******************************************\n");
	// printf("*%9.9s	|	%s\n", "CONTENT", "CATEGORY 	 *");
	// printf("******************************************\n\n");
	// while (tokens != NULL)
	// {
	// 	// printf("%s is %d\n", tokens[i], get_category(tokens[i]));
	// 	// printf("%s - %d\n", tokens->word, tokens->category);
	// 	// ft_putstr_fd(tokens->word, 1);
	// 	// ft_putstr_fd("	", 1);
	// 	// ft_putnbr_fd(tokens->category, 1);
	// 	// ft_putstr_fd("\n", 1);
	// 	printf("%-9s	|	%-d\n", tokens->word, tokens->category);
	// 	// printf("%s", tokens->word);
	// 	tokens = tokens->next;
	// }
	return (0);
}