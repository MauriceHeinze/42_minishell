#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
# include "../readline/readline.h"
# include "../readline/history.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/ioctl.h>
# include "../libft/libft.h"


typedef struct s_fd {
	int				io; // 0 stdin, 1 stdout
	int				mode; // 1. file -> full path, 2. heredoc -> delimiter, 3. stdin -> nothing 4. append mode -> full path
	char			*meta; // full path || delimiter
	int				fd; // Ralf only
	struct s_fd		*next;
}				t_fd;

typedef struct s_node {
	char			*full_cmd; // e.g. echo -n, cd etc.
	char			*full_cmd_orig; // e.g. echo -n, cd etc.
	char			*full_path; // if builtin, then it's just full_cmd, else it's path to that cmd
	int				pid; // default -1, is set by executor
	t_fd			*fd;
	struct s_node	*next;
}				t_node;

typedef struct s_var {
	char			*name;
	char			*content;
	char			*not_splitted;
	struct s_var	*next;
}				t_var;


typedef struct s_program {
	t_var			*envp;
	int				status;
	char			*cmd_line;
	char			**tokens;
	t_node			*nodes;
}				t_program;

t_program *program;

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
t_node	*fill_node(t_program *program);
t_fd	*setup_fd(void);
void	fill_fd(t_program *program, t_node *node, int *pos);
void	setup_signal_handler(void);
void	track_history(char *line);
void	ctrl_c(void);
t_var	*setup_var_node(void);
t_var	*store_env(char *env[]);
char	*get_env(t_var *env, char *name);
t_var	*add_env(t_var *env, char *name, char* content);
void    remove_env(t_var *env, char *name);
void	rl_replace_line (const char *text, int clear_undo);


// Executor
char	*get_cmd_path(char **paths, char *cmd);
char	**get_cmd_paths(t_var *envp);

// free
void	free_nodes(t_program *program);

# define OUTPUT 0;
# define INPUT 1;

// KEYS FOR BUILT INS
# define UNDEFINED 50
# define ECHO_CMD 100
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

// MODES
# define MODE_FILE 10000
# define MODE_HEREDOC 10100
# define MODE_STDIN 10200
# define MODE_APPEND 10300
# define MODE_PIPE 10400

#endif
