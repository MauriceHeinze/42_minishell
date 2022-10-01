#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

# include <stdio.h>
# include "../libft/libft.h"

struct token {
	char			*word;
	int				type; // Use define function
	struct token	*next;
};

struct cmd_line {
	char				*cmd;
	struct token		*word;
	char				**args;
	struct cmd_line		*next;
};

#endif
