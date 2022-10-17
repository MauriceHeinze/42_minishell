#include "../inc/minishell.h"

int	g_status;

g_status = 0;


int	main(int argc, char *argv[])
{
	char	*line;

	setup_signal_handler();

	while (1)
	{
		line = readline("\e[1;92mminishell\e[1;94m $\e[0;37m ");
		if (line[0] != '\0')
			add_history(line);
		printf("%s\n", line);
		free(line);
	}
	// add_history("test");
	return (0);
}