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

typedef struct s_token {
	char			*word;
	int				category; // Use define function
	struct s_token	*next;
}				t_token;

typedef struct s_cmd_line {
	char				*cmd;
	t_token				*word;
	char				**args;
	struct s_cmd_line	*next;
}				t_cmd_line;

// TOOLS
int		get_category(char *word);
char	special_char(char *input_str, int pos);
char	**split_line(char *input_str);
char	*copy_quote(char found_quote, char *input_str, int pos);
int		quote_length(char found_quote, char *input_str, int pos);
int		count_words(char *input_str);
t_token	*tokenizer(char	**words);
char	*ft_substr_backslash(char const *s, unsigned int start, size_t len);
char	**split_subline(char **words);
char	*remove_quotes(char *input_str);
int		count_words_operators(char *input_str);

// KEYS FOR BUILT INS
# define UNDEFINED 50
# define ECHO 100
# define CD 200
# define PWD 300
# define EXPORT 400
# define UNSET 500
# define ENV 600
# define EXIT 700

// KEYS FOR OPERATORS
# define ARROW_LEFT 800
# define DOUBLE_ARROW_LEFT 900
# define ARROW_RIGHT 1000
# define DOUBLE_ARROW_RIGHT 1100
# define PIPE 1200
# define OR 1300
# define AND 1400

// KEYS FOR WORDS, WHITE-SPACE AND QUOTES
# define WHITE_SPACE 1500
# define QUOTE 1600
# define DOUBLE_QUOTE 1700
# define WORD 1900
# define VARIABLE 2000

#endif
