#include "../inc/minishell.h"

t_token	*tokenizer(char	**words)
{
	int		i;
	t_token	*head;
	t_token	*tmp_token;
	t_token	*tmp_token_2;

	head = malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	head->word = ft_strdup(words[0]);
	head->category = get_category(words[0]);
	head->next = NULL;
	tmp_token_2 = head;
	i = 1;
	while (words[i] != NULL)
	{
		// printf("Loop #%d		'%s'	", i, words[i]);
		tmp_token = malloc(sizeof(t_token));
		tmp_token->word = ft_strdup(words[i]);
		tmp_token->category = get_category(words[i]);
		// printf("Category #%d\n", tmp_token->category);
		tmp_token->next = NULL;
		tmp_token_2->next = tmp_token;
		tmp_token_2 = tmp_token;
		i++;
	}
	return (head);
}

int	main(int argc, char *argv[])
{
	char		*input_str = " 	   	cd ../Desktop | echo \"Hallo Welt!\" >> file.txt 	 	 ";
	char		**words;
	t_token		*tokens;

	// tokens = malloc(sizeof(tokens));

	// printf("Test %d\n", is_command("echo"));

	input_str = ft_strtrim(input_str, " 	");
	// printf("%s\n", input_str);
	printf("Number of words: %d\n", count_words(input_str));
	// words = split_line(input_str);
	// tokens = tokenizer(words);

	// printf("%s\n", words[14]);
	// words[14] = NULL;

	// int i = 0;
	// while (words[i] != NULL)
	// 	printf("%s\n", words[i++]);
	// printf("%s", tokens->word);
	// tokens = tokens->next;
	// printf("%s", tokens->word);

	// printf("spaces: %d\n", count_spaces("cd ../Desktop | echo \"Hallo Welt!\" >> file.txt"));
	// while (tokens != NULL)
	// {
	// 	// printf("%s is %d\n", tokens[i], get_category(tokens[i]));
	// 	// printf("%s - %d\n", tokens->word, tokens->category);
	// 	// ft_putstr_fd(tokens->word, 1);
	// 	// ft_putstr_fd("	", 1);
	// 	// ft_putnbr_fd(tokens->category, 1);
	// 	// ft_putstr_fd("\n", 1);
	// 	printf("%s\n", tokens->word);
	// 	// printf("%s", tokens->word);
	// 	tokens = tokens->next;
	// }
	return (0);
}