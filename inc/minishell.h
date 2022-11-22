/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_cmd_path.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mheinze <mheinze@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/10/04 21:08:49 by mheinze		   #+#	#+#			 */
/*   Updated: 2022/11/22 16:15:23 by mheinze		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
# include "../readline/readline.h"
# include "../readline/history.h"
# include "./libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/ioctl.h>

typedef struct s_fd {
	int				io; // 0 stdin, 1 stdout
	int				mode; // 1. file -> full path, 2. heredoc -> delimiter, 3. stdin -> nothing 4. append mode -> full path
	char			*meta; // full path || delimiter
	int				fd; // Ralf only
	struct s_fd		*next;
}				t_fd;

typedef struct s_node {
	char			*full_cmd; // e.g. echo -n, cd etc.
	char			*full_cmd_orig;
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

// split
char	**split_line(char *input_str);
char	**split_subline(char **words);

// readline
void	track_history(char *line);
void	rl_replace_line (const char *text, int clear_undo);

// quotes
int		quote_length(char found_quote, char *input_str, int pos);
int		skip_quote(char *input_str, int pos);
char	*remove_quotes(char *input_str);

// manipulate string
char	*str_add(char *dest, char *src, int pos);
char	*str_remove(char const *orig, unsigned int start, size_t len);

// variables
char	*expand_variable(char *input_str, int start, int i);
char	*expand_variables(char *input_str);

// env
t_var	*store_env(char *env[]);
char	*get_env(t_var *env, char *name);
t_var	*add_env(t_var *env, char *name, char* content);
void	remove_env(t_var *env, char *name);

// signals
void	setup_signal_handler(void);
void	ctrl_c(void);

// commands
t_node	*fill_node(t_program *program);
void	fill_fd(t_program *program, t_node *node, int *pos);
t_fd	*setup_fd(void);

// free
void	free_nodes(t_program *program);

// syntax checker
int		check_syntax(char **tokens);
int		is_operator(char *word);

// exit
void	exit_shell(int error_code);
void	set_exit_code(int exit_code);
void	exec_error(int error, char *s);
void	special_error(int error);

// utils
int		count_words(char *input_str);
int		count_words_operators(char *input_str);
char	*get_cmd_path(char **paths, char *cmd);
char	**get_cmd_paths(t_var *envp);
int		get_category(char *word);
int		is_whitespace(char *input_str);

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

// ERROR CODES
# define SINGLE_QUOTE_MISSING		1
# define DOUBLE_QUOTE_MISSING		2
# define REDIR_SYNTAX_ERROR			3
# define EXIT_ERROR					4
# define CMD_ERROR					5
# define EXIT_ARG_ERROR				6
# define INVALID_PATH				7
# define EXPORT_ERROR				8
# define OLDPWD_ERROR				9
# define UNSET_ERROR				10
# define PATH_ERROR					11
# define PERMISSION_ERROR			12
# define EMPTY_KEY_ERROR			13
# define ENV_ERROR					14
# define SEMICOLON_USED				15

# define CMD_NOT_FOUND				127
# define INVALID_EXIT_ARG			255
# define TERMINATED_BY_CTRL_C		130
# define PIPE_SYNTAX_ERROR			258

#endif
