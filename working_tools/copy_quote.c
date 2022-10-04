#include "../inc/minishell.h"

char	*copy_quote(char found_quote, char *input_str)
{
	int		i;
	int		k;
	char	*quote;

	i = 0;
	k = 0;
	quote = malloc(sizeof(char) * ft_strlen(input_str));
	while (input_str[i] != '\0')
	{
		if (input_str[i] == found_quote)
			break ;
		else
		{
			if (input_str[i] == '\\')
			{
				i++;
				quote[k] = input_str[i++];
			}
			else
				quote[k] = input_str[i++];
			k++;
		}
	}
	quote[k] = '\0';
	return (quote);
}
