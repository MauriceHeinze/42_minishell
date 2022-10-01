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