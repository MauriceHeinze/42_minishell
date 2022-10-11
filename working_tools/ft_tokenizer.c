#include "../inc/minishell.h"

t_token	*tokenizer(char	**words)
{
	int		i;
	t_token	*head;
	t_token	*tmp_token;
	t_token	*tmp_token_2;

	printf("First word in tokenizer: %s\n", words[0]);
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