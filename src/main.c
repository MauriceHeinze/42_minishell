#include "../inc/minishell.h"

int	main(int argc, char *argv[])
{
	// char		*input_str = " 	   	cd ../Desktop | echo \"Hallo Welt!\" >> file.txt 	 	 ";
	// char		*input_str = " 	   	cd ../Desktop | touch file_21.txt | echo \"Hallo Welt!\" >> file.txt 	 	 ";
	// char	*input_str = "echo               text \"$USER\"            \"$USER\"text";
	char	*input_str = "<Makefile cat| echo \"$PWD $e 'hola'\" ~/src | 'tr' -d / >outfile";
	// char	*input_str = "aaa>bbb>ccc&&ddd>>";

	char		**words;
	t_token		*tokens;
	int			i;

	i = 0;
	// printf("Path is %zu\n", ft_strlen(getenv("PATH")));
	// printf("Var len is %d\n", get_var_len(input_str));

	char	*orig = "Hallo Welt";
	char	*new_part = " meine";
	int		pos = 11;

	printf("%s \n", orig);
	orig = str_add(orig, new_part, pos);
	printf("%s \n", orig);
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