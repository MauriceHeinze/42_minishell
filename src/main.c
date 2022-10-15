#include "../inc/minishell.h"

int	main(int argc, char *argv[])
{
	// char		*input_str = " 	   	cd ../Desktop | echo \"Hallo Welt!\" >> file.txt 	 	 ";
	// char		*input_str = " 	   	cd ../Desktop | touch file_21.txt | echo \"Hallo Welt!\" >> file.txt 	 	 ";
	// char	*input_str = "echo               text \"$USER\"            \"$USER\"text";
	// char	*input_str = "<Makefile cat| echo \"$PWD $e 'hola'\" ~/src | 'tr' -d / >outfile";
	// char	*input_str = "aaa>bbb>ccc&&ddd>>";
	char	*input_str = "echo $PWD/path | echo $USER";

	// char		**words;
	// t_token		*tokens;
	int			i;

	i = 0;

	// input_str = str_remove_word(input_str, 6, 4);
	// printf("%s\n", input_str);

	// printf("Path is %zu\n", ft_strlen(getenv("PATH")));
	// printf("Var len is %d\n", get_var_len(input_str));

	printf("%s\n", input_str);
	input_str = expand_variables(input_str);
	printf("%s\n", input_str);

	// char	*orig = "Hallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo WeltHallo Welt";
	// char	*new_part = " meine";
	// int		pos = 11;

	// printf("%s \n", orig);
	// orig = str_add("echo $PWD/ddfgg | echo $USER", "/Users/mheinze/Desktop/Projects/minishell", 5);
	// printf("%s \n", orig);
	// input_str = ft_strjoin("Hallo", &input_str[10]);

	// input_str = ft_strtrim(input_str, " 	");
	// input_str = expand_variables(input_str);
	// words = split_line(input_str);
	// words = split_subline(words);
	// while (words[i] != NULL)
	// {
	// 	words[i] = remove_quotes(words[i]);
	// 	printf("%s\n", words[i]);
	// 	i++;
	// }
	return (0);
}