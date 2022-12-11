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
# include "../get_next_line/get_next_line.h"
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
	int				fd_in;
	int				fd_out;
	int				fd_in_found;
	int				fd_out_found;
	struct s_node	*next;
	int				node_num;
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
	char			**tokens;
	char			*unknown_cmd;
	t_node			*nodes;
}				t_program;

t_program *program;

// split
char	**split_line(char *str);
char	**split_subline(char **splitted);

int		split_line_counter(char *str);
void	acutal_split(char **splits, char **words, int *i, int *no_word);
int		double_operator_found(char a, char b);

// fill node
int		get_command(t_program *program, t_node **node, int *pos);
t_node	*add_node(t_node *node, int *i);
t_node	*setup_node(void);
int	add_tokens(t_node **node, char **tokens, int *i);

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
t_var	*setup_var_node(void);
t_var	*store_env(char *env[]);
char	*get_env(t_var *env, char *name);
t_var	*add_env(t_var *env, char *name, char* content);
void	remove_env(t_var *env, char *name);
void	free_env(void);

// signals
void	setup_signal_handler(void);
void	ctrl_c(void);

// commands
t_node	*fill_node(t_program *program);
// int	fill_fd(t_program *program, t_node **node, int *pos);
void	fill_fd(t_program *program, t_node **node, int *pos);

t_fd	*setup_fd(void);

// free
void	free_nodes(void);
void	free_split(char **words);
t_node	*free_head(t_node *head);

// syntax checker
int		check_syntax(char **tokens);
int		is_operator(char *word);

// exit
void	exit_shell(int error_code);
void	set_exit_code(int exit_code);
void	exec_error(int error, char *s);
void	special_error(int error);
void	builtin_error(int error, char *s);

// utils
int		count_words(char *str);
int		op_found(char a, char b);
int		count_words_operators(char *input_str);
char	*get_cmd_path(char **paths, char *cmd);
char	**get_cmd_paths(t_var *envp);
char	*get_cmd_path_no_free(char **paths, char *cmd);
int		get_category(char *word);
void	init_to_zero(int *a, int *b, int *c, int *d);
int		is_whitespace(char *input_str);
void	fd_handle_redirection(int category, t_node *node, t_fd *fd, int *pos);

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
# define EXIT_NUM_ERROR				16
# define HEREDOC_BUFFER_ERROR		17
# define DUP_ERROR					18
# define PIPE_ERROR					19
# define FORK_ERROR					20
# define GETCWD_ERROR				21
# define CHDIR_ERROR				22
# define ADD_ENV_ERROR				23
# define BULTIN_NF_ERROR			24

# define CMD_NOT_FOUND				127
# define INVALID_EXIT_ARG			255
# define TERMINATED_BY_CTRL_C		130
# define PIPE_SYNTAX_ERROR			258

# define PATH_MAX					4096

#endif
