#include "../inc/minishell.h"

// lexer -> expander ->  parser -> executor

// Steps
// break string apart
// order string by types

// reduces strings by reducing all delimiting chars in a row to one
char *ft_strred(char *cmd_line)
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
		}
		i++;
	}
	return (reduced_str);
}

int	main(int argc, char *argv[])
{
	// char	*cmd_line = "\techo\t \"Hallo meine Welt\"";

	// printf("%s\n", cmd_line);
	// printf("%d\n", is_separator('|'));
	printf("%s", ft_strred("  	Hallo   'meine   Welt'  test   "));
	printf("abc");
	// found_cmd(cmd_line);
	return (0);
}