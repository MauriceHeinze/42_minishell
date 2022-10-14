#include "../inc/minishell.h"

static int	count_operator_helper(char *input_str)
{
	int	i;
	int	no_operators;

	i = 0;
	no_operators = 0;
	while (input_str[i] != '\0')
	{
		if ((input_str[i] == '<') && (input_str[i + 1] == '<') ||
			(input_str[i] == '>') && (input_str[i + 1] == '>') ||
			(input_str[i] == '&') && (input_str[i + 1] == '&') ||
			(input_str[i] == '|') && (input_str[i + 1] == '|'))
		{
			i++;
			no_operators++;
		}
		else if ((input_str[i] == '<') || (input_str[i] == '>'))
			no_operators++;
		else if (input_str[i] == '|')
			no_operators++;
		i++;
	}
	return (no_operators);
}

static int	operator_start(char *input_str)
{
	if ((input_str[0] == '<') && (input_str[1] == '<') ||
			(input_str[0] == '>') && (input_str[1] == '>') ||
			(input_str[0] == '&') && (input_str[1] == '&') ||
			(input_str[0] == '<') || (input_str[0] == '>') || (input_str[0] == '|'))
				return (1);
	return (0);
}

static int	operator_end(char *input_str)
{
	int	len;

	len = ft_strlen(input_str);
	if ((input_str[len - 1] == '<') && (input_str[len - 2] == '<') ||
			(input_str[len - 1] == '>') && (input_str[len - 2] == '>') ||
			(input_str[len - 1] == '&') && (input_str[len - 2] == '&') ||
			(input_str[len - 1] == '<') || (input_str[len - 1] == '>') || (input_str[len - 1] == '|'))
				return (1);
	return (0);
}

// use function only on strings that are bigger than one
int	count_words_operators(char *input_str)
{
	int	no_operators;
	int	operator_start_end;
	int additional_operators;

	additional_operators = 0;
	if (ft_strlen(input_str) > 0 && ft_strlen(input_str) < 2)
		return (1);

	if (ft_strlen(input_str) == 0)
		return (0);
	no_operators = count_operator_helper(input_str);
	if (operator_start(input_str))
		additional_operators++;
	if (operator_end(input_str))
		additional_operators++;

	return ((no_operators * 2) + 1 - additional_operators);
}


// printf("Should be 11:	%d\n", count_words_operators("x>x>x>x>x>x"));
// printf("Should be 10:	%d\n", count_words_operators(">x>x>x>x>x"));
// printf("Should be 9:	%d\n", count_words_operators("x>x>x>x>x"));
// printf("Should be 8:	%d\n", count_words_operators(">x>x>x>x"));
// printf("Should be 7:	%d\n", count_words_operators("x>x>x>x"));
// printf("Should be 6:	%d\n", count_words_operators(">x>x>x"));
// printf("Should be 5:	%d\n", count_words_operators("x>x>x"));
// printf("Should be 4:	%d\n", count_words_operators(">x>x"));
// printf("Should be 3:	%d\n", count_words_operators("x>x"));
// printf("Should be 2:	%d\n", count_words_operators("x>"));
// printf("Should be 1:	%d\n", count_words_operators(">"));
// printf("Should be 0:	%d\n", count_words_operators(""));