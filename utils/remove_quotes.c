#include "../inc/minishell.h"

char	*remove_quotes(char *input_str)
{
	int	len;
	char *shortend;

	len = ft_strlen(input_str) - 1;
	if ((input_str[0] == '\'' && input_str[len] == '\'') ||
		(input_str[0] == '\"' && input_str[len] == '\"'))
	{
		shortend = ft_substr(input_str, 1, len - 1);
		free(input_str);
		return (shortend);
	}
	return (input_str);
}