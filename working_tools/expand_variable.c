#include "../inc/minishell.h"

static char	*expand_variable(char *input_str, int start, int i)
{
	char	*var_name;

	var_name = ft_substr(input_str, start, i - start);
	input_str = str_remove_word(input_str, start, i - start + 1);
	input_str = str_add(input_str, getenv(var_name), start);
	free(var_name);
	return (input_str);
}

char	*expand_variables(char *input_str)
{
	int		i;
	int		start;

	i = 0;
	// get number of chars of variables
	while (input_str[i] != '\0')
	{
		if (input_str[i] == '\'')
			i = skip_quote(input_str, i);
		else if (input_str[i] == '$' && (ft_isalpha(input_str[i + 1]) || input_str[i + 1] == '_'))
		{
			i++;
			start = i;
			while (input_str[i] != '\0' && input_str[i] != '/' && (ft_isalpha(input_str[i]) || ft_isalnum(input_str[i]) || input_str[i] == '_'))
				i++;
			input_str = expand_variable(input_str, start, i);
			i = 0;
			start = 0;
		}
		else if (input_str[i] == '~' && (ft_strchr("/ 	", input_str[i + 1])))
		{
			i++;
			start = i;
			input_str = str_remove_word(input_str, start, i - start + 1);
			input_str = str_add(input_str, getenv("HOME"), start);
			i = 0;
			start = 0;
		}
		else
			i++;
	}
	return (input_str);
}
