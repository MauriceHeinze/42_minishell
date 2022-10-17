#include "../inc/minishell.h"

// gcc ./src/main.c ./inc/minishell.h ./libft/libft.a ./working_tools/*.c -lreadline -L /goinfre/mheinze/.brew/opt/readline/lib -I /goinfre/mheinze/.brew/opt/readline/include

int	g_status = 0;

static void do_shell(char *input_str)
{
	char	**words;
	int		i;

	i = 0;
	input_str = expand_variables(input_str);
	input_str = ft_strtrim(input_str, " 	");
	input_str = expand_variables(input_str);
	words = split_line(input_str);
	words = split_subline(words);
	while (words[i] != NULL)
	{
		words[i] = remove_quotes(words[i]);
		printf("%s\n", words[i]);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	char	*line;

	setup_signal_handler();
	while (1)
	{
		line = readline("minishell $");
		track_history(line);
		do_shell(line);
		free(line);
	}
	return (0);
}
