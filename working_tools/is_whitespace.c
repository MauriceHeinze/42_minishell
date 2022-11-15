#include "../inc/minishell.h"

int	is_whitespace(char *input_str)
{
	int	i;

	i = 0;

	while (input_str[i] == ' ' || input_str[i] == '	')
		i++;
	if (input_str[i] == '\0')
		return (1);
	else
		return (0);
}