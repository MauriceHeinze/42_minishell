#include "../inc/minishell.h"

// gcc ./src/main.c ./inc/minishell.h ./libft/libft.a ./working_tools/*.c -lreadline -L /goinfre/mheinze/.brew/opt/readline/lib -I /goinfre/mheinze/.brew/opt/readline/include

int	g_status = 0;

int	main(int argc, char *argv[])
{
	char	*line;

	setup_signal_handler();

	while (1)
	{
		line = readline("\e[1;92mminishell\e[1;94m $\e[0;37m ");
		if (line == NULL)
			return (0); // exit shell
		if (line[0] != '\0')
			add_history(line);
		printf("%s\n", line);
		free(line);
	}
	return (0);
}