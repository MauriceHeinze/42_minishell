#include "../inc/minishell.h"

static int	is_uppercase(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

char	*expand_variables(char *input_str)
{
	int		i;
	int		var_len;
	int		start;
	char	*var_name;

	i = 0;
	var_len = 0;
	// get number of chars of variables
	while (input_str[i] != '\0')
	{
		if (input_str[i] == '$' && (ft_isalpha(input_str[i + 1]) || input_str[i + 1] == '_'))
		{
			i++;
			start = i;
			while (input_str[i] != '\0' && input_str[i] != '/' && (ft_isalpha(input_str[i]) || ft_isalnum(input_str[i]) || input_str[i] == '_'))
				i++;
			var_name = ft_substr(input_str, start, i - start);
			input_str = str_remove_word(input_str, start, i - start + 1);
			input_str = str_add(input_str, getenv(var_name), start);
			free(var_name);
			i = 0;
			start = 0;
		}
		i++;
	}
	return (input_str);
}
