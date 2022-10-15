#include "../inc/minishell.h"

static int	is_uppercase(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	get_var_len(char *input_str)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = 0;

	// get number of chars of variables
	while (input_str[i] != '\0')
	{
		// printf("%d\n", is_uppercase(input_str[i + 1]));
		if (input_str[i] == '$' && is_uppercase(input_str[i + 1]))
		{
		printf("test\n");
			var_len++;
			i++;
			while (input_str[i] != '\0' && (is_uppercase(input_str[i]) || input_str[i] == '_'))
			{
				var_len++;
				i++;
			}
		}
		i++;
	}
	return (var_len);
}