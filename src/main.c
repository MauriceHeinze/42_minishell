#include "../inc/minishell.h"

int	main(int argc, char *argv[])
{
	// char		*input_str = " 	   	cd ../Desktop | echo \"Hallo Welt!\" >> file.txt 	 	 ";
	// char		*input_str = " 	   	cd ../Desktop | touch file_21.txt | echo \"Hallo Welt!\" >> file.txt 	 	 ";
	// char	*input_str = "echo               text \"$USER\"            \"$USER\"text";
	// char	*input_str = "<Makefile cat| echo \"$PWD $e 'hola'\" ~/src | 'tr' -d / >outfile";
	// char	*input_str = "aaa>bbb>ccc&&ddd>>";
	char	*input_str = "echo ~/path | echo home is: ~";

	char		**words;
	int			i;

	i = 0;

	printf("\n%s\n------------------\n", input_str);
	input_str = expand_variables(input_str);
	printf("%s\n", input_str);

	input_str = ft_strtrim(input_str, " 	");
	input_str = expand_variables(input_str);
	words = split_line(input_str);
	words = split_subline(words);
	// while (words[i] != NULL)
	// {
	// 	words[i] = remove_quotes(words[i]);
	// 	printf("%s\n", words[i]);
	// 	i++;
	// }
	return (0);
}