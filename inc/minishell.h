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

typedef struct	s_token {
	char			*word;
	int				type; // Use define function
	struct token	*next;
}				t_token;

struct	s_cmd_line {
	char				*cmd;
	struct token		*word;
	char				**args;
	struct cmd_line		*next;
}		t_cmd_line;

#endif
