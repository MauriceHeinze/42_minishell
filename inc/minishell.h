#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>


typedef struct s_token {
	char				*word;
	int					category; // Use define function
	struct s_token		*next;
}				t_token;

typedef struct s_cmd_line {
	char				*cmd;
	t_token				*word;
	char				**args;
	struct s_cmd_line	*next;
}				t_cmd_line;

typedef struct s_node {
	char				*full_cmd; // e.g. echo, cd etc.
	char				*full_path; // if builtin, then it's just full_cmd, else it's path to that cmd
	int					pid; // default -1, is set by executor
	int					infile_mode;
	char				*infile_meta; // 1. file -> full path, 2. heredoc -> delimiter, 3. stdin -> nothing
	int					outfile_mode;
	char				*outfile_meta; // 1. file -> full path, 2. stderr -> nothing, 3. stdin -> nothing
	struct s_cmd_line	*next;
}				t_node;

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
char	*str_add(char *dest, char *src, int pos);
char	*expand_variables(char *input_str);
char	*str_remove_word(char const *orig, unsigned int start, size_t len);
int		skip_quote(char *input_str, int pos);

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
