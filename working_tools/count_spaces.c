#include "../inc/minishell.h"

static int	count_spaces(char *input_str)
{
	int	i;
	int	no_spaces;
	int	count;

	i = 0;
	no_spaces = 0;
	count = 1;
	while (input_str[i] != '\0' && (input_str[i] == ' ' || input_str[i] == '	'))
		i++;
	while (input_str[i] != '\0')
	{
		if ((input_str[i] == '\'' || input_str[i] == '\"') && count == 1)
			count = 0;
		else if ((input_str[i] == '\'' || input_str[i] == '\"') && count == 0)
			count = 1;
		if (count == 0)
			i++;
		else if (count == 1)
		{
			if (input_str[i] == ' ' || input_str[i] == '	')
				no_spaces++;
			i++;
		}
	}
	return (no_spaces);
}

int	count_words(char *input_str)
{
	int	no_spaces;

	if (ft_strlen(input_str) == 0)
		return (0);
	no_spaces = count_spaces(input_str);
	if (ft_strlen(input_str) > 0 && no_spaces == 0)
		return (1);
	else
		return (no_spaces + 1);
}