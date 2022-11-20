#include "../inc/minishell.h"

static int	count_spaces(char *input_str)
{
	int	i;
	int	no_spaces;
	int	count;

	i = 0;
	no_spaces = 0;
	count = 1;
	while (input_str[i] != '\0' && ft_strchr(" 	", input_str[i]))
		i++;
	while (input_str[i] != '\0')
	{
		if (ft_strchr("\'\"", input_str[i]))
		{
			if (i > 0 && !ft_strchr(" 	", input_str[i - 1])) // if previous char isn't a space
			{
				// printf("4: counted up at	%c at pos %d\n", input_str[i], i);
				no_spaces++;
				i++;
			}
			i = skip_quote(input_str, i); // jumps to char after quote

			if (!ft_strchr(" 	", input_str[i])) // if this char is no space, count up
			{
				// printf("1: counted up at	%c at pos %d\n", input_str[i], i);
				no_spaces++;
			}
		}
		if (ft_strchr(" 	", input_str[i])) // if char is space, count up
		{
			// printf("2: counted up at	%c at pos	%d\n", input_str[i], i + 1);
			if (input_str[i + 1] == '\0')
				break;
			no_spaces++;
		}
		i++;
	}
	if (input_str[i] == '\0')
	{
		// printf("3: counted up at	%c at pos	%d\n", input_str[i], i + 1);
		no_spaces++;
	}
	printf("Number of words:	%d\n", no_spaces);
	return (no_spaces);
}
// echo hallo | echo "ciao" | echo hi // 8
// echo hallo | echo "ciao" | echo 'hi' // 8
// echo hallo | echo "ciao" | echo welt'hi'  // 9
// echo hallo | echo "ciao" | echo 'hi'test // 9

int	count_words(char *input_str)
{
	int	no_spaces;

	if (ft_strlen(input_str) == 0)
		return (0);
	no_spaces = count_spaces(input_str);
	if (ft_strlen(input_str) > 0 && no_spaces == 0)
		return (1);
	else
		return (no_spaces);
}


// #include "../inc/minishell.h"

// static int	count_spaces(char *input_str)
// {
// 	int	i;
// 	int	no_spaces;
// 	int	count;

// 	i = 0;
// 	no_spaces = 0;
// 	count = 1;
// 	while (input_str[i] != '\0' && ft_strchr(" 	", input_str[i]))
// 		i++;
// 	while (input_str[i] != '\0')
// 	{
// 		if (ft_strchr("\'\"", input_str[i]))
// 		{
// 			i = skip_quote(input_str, i);
// 			printf("char is:	%c\n", input_str[i - 1]);
// 			printf("char is:	%c\n", input_str[i]);
// 			printf("char is:	%c\n=====\n", input_str[i + 1]);
// 			if (input_str[i] == '\0')
// 			{
// 				printf("stop\n");
// 				break;
// 			}
// 			if (!ft_strchr(" 	", input_str[i]))
// 			{
// 				printf("hej\n");
// 				no_spaces++;
// 			}
// 		}
// 		if (ft_strchr(" 	", input_str[i]))
// 			no_spaces++;
// 		if (input_str[i + 1] == '\0')
// 			no_spaces++;
// 		i++;
// 	}
// 	printf("Number of words: %d\n", no_spaces);
// 	return (no_spaces);
// }
// // echo hallo | echo "ciao" | echo hi // 8
// // echo hallo | echo "ciao" | echo 'hi' // 8
// // echo hallo | echo "ciao" | echo welt'hi'  // 9
// // echo hallo | echo "ciao" | echo 'hi'test // 9

// int	count_words(char *input_str)
// {
// 	int	no_spaces;

// 	if (ft_strlen(input_str) == 0)
// 		return (0);
// 	no_spaces = count_spaces(input_str);
// 	if (ft_strlen(input_str) > 0 && no_spaces == 0)
// 		return (1);
// 	else
// 		return (no_spaces);
// }