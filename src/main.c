#include "../inc/minishell.h"

// lexer -> expander ->  parser -> executor

// Steps
// break string apart
// order string by types

// reduces strings by reducing all delimiting chars in a row to one
char	*ft_strred(char *cmd_line)
{
	int		i;
	int		k;
	int		end;
	char	*reduced_str;
	int		reduce;

	i = 0;
	k = 0;
	reduce = 1;
	reduced_str = malloc(sizeof(char) * ft_strlen(cmd_line));
	if (!reduced_str)
		return (NULL);
	while (cmd_line[i++] != '\0')
	end = i - 1;
	i = 0;
	while (cmd_line[end] <= 32)
		end--;
	while (cmd_line[i] <= 32)
		i++;
	while (cmd_line[i] != '\0')
	{
		// printf("Index	%d|	Char:	%c|	Reduce: %d\n", i, cmd_line[i], reduce);
		if (cmd_line[i] == '\'' && reduce == 1)
			reduce = 0;
		else if (cmd_line[i] == '\'' && reduce == 0)
			reduce = 1;
		if (reduce == 0)
			reduced_str[k++] = cmd_line[i];
		else if (reduce == 1)
		{
			if (cmd_line[i] > 32)
			{
				reduced_str[k++] = cmd_line[i];
				if (cmd_line[i + 1] <= 32 && (i < end) && reduce)
					reduced_str[k++] = cmd_line[i + 1];
			}
			reduced_str[k] = '\0';
		}
		i++;
	}
	return (reduced_str);
}

int		get_no_cmd_lines(char *input_str)
{
	int		i;
	int		no_cmd_lines;

	i = 0;
	no_cmd_lines = 1;
	while (input_str[i] != '\0')
	{
		if (input_str[i] == '|')
			no_cmd_lines++;
		i++;
	}
	return (no_cmd_lines);
}

char	**split_cmd_lines(char *input_str)
{
	int		i;
	int		no_cmd_lines;
	char	**cmd_lines;

	i = 0;
	cmd_lines = ft_split(input_str, '|');
	while (cmd_lines[i] != NULL)
	{
		cmd_lines[i] = ft_strred(cmd_lines[i]);
		i++;
	}
	return (cmd_lines);
}

// // creates tokens out of reduced cmd_line
// char	**tokenizer(char *reduced_cmd_line)
// {
// 	int		cmd_i;
// 	int		token_i;
// 	int		tokens_k;
// 	char	*token;
// 	char	**tokens;

// 	cmd_i = 0;
// 	token_i = 0;
// 	tokens_k = 0;
// 	token = malloc(sizeof(token) * 10000);
// 	tokens = malloc(sizeof(token) * 10000);

// 	while (reduced_cmd_line[cmd_i] != '\0')
// 	{
// 		while (is_delimiter(reduced_cmd_line[cmd_i]) == 0)
// 		{
// 			tokens[tokens_k][token_i] = reduced_cmd_line[cmd_i];
// 			token_i++;
// 			cmd_i++;
// 		}
// 		tokens[tokens_k][token_i] = '\0';
// 		tokens_k++;
// 	}
// }

int	main(int argc, char *argv[])
{
	// char	*cmd_line = "\techo\t \"Hallo meine Welt\"";

	// printf("%s\n", cmd_line);
	// printf("%d\n", is_separator('|'));
	// printf("%s", ft_strred("'  	Hallo   meine   Welt'  test   "));

	char	**tab;
	int		i;

	i = 0;
	tab = split_cmd_lines("echo Hallo Welt | touch file |");

	if (!tab[0])
		ft_putendl_fd("ok\n", 1);
	while (tab[i] != NULL)
	{
		ft_putendl_fd(tab[i], 1);
		i++;
	}
	// found_cmd(cmd_line);
	return (0);
}
