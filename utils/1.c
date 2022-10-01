#include "../inc/minishell.h"

int	is_separator(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else if (c == '\t')
		return (3);
	else if (c == '|')
		return (4);
	return (0);
}

void	found_cmd(char *cmd_line)
{
	char	**tokens;
	int		i;

	i = 0;
	tokens = ft_split(cmd_line, ' ');

	while (tokens[i] != NULL)
	{
		printf("%s\n", tokens[i]);
		i++;
	}
}

// reduces strings by reducing all delimiting chars in a row to one
char *ft_strred(char *cmd_line)
{
	int		i;
	int		k;
	int		end;
	char	*tmp;
	int		reduce;

	i = 0;
	k = 0;
	reduce = 1;
	tmp = malloc(sizeof(char) * ft_strlen(cmd_line));
	if (!tmp)
		return (NULL);
	while (cmd_line[i++] != '\0')
	end = i - 1;
	i = -1;
	while (cmd_line[end] == ' ')
		end--;
	while (cmd_line[i++] == ' ');
	while (cmd_line[i] != '\0')
	{
		if (cmd_line[i] == '\'' && reduce == 1)
			reduce = 0;
		else if (cmd_line[i] == '\'' && reduce == 0)
			reduce = 1;
		if (reduce == 0)
			tmp[k++] = cmd_line[i];
		else if (reduce == 1)
		{
			if (cmd_line[i] != ' ')
			{
				tmp[k++] = cmd_line[i];
				if (cmd_line[i + 1] == ' ' && (i < end) && reduce)
					tmp[k++] = cmd_line[i + 1];

			}
		}
		i++;
	}
	return (tmp);
}