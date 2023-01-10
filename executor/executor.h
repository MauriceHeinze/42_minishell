/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:05:47 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/18 12:39:40 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include "../inc/minishell.h"

typedef struct s_executor
{
	int		*pipes;
	int		num_pipes;
	int		num_processes;
	pid_t	*pids;
	char	**cmd_paths;
	char	*limiter;
	char	*buffer;
	int		status;
	t_node	*first_node;
	int		heredoc;
	int		last_builtin_exit;
}	t_executor;

void	close_fd(t_executor *executor);

void	close_other_fd(t_executor *executor, int fd1, int fd2);

void	create_pipes(t_executor *executor);

void	dup2_close_other(t_executor *executor, int pid, t_node *node);

void	dup2_processor(int out, int in, int exit_code);

void	here_doc(char *argv, t_executor *executor);

void	here_doc_open(t_executor *executor);

char	*get_cmd_path(char **paths, char *cmd);

int		builtin_caller(t_node *node, t_executor *executor, t_var *envp);

int		executor(t_node *node, t_var *envp);

void	free_double_ptr(char **ptr);

int		exit_pre_handler(t_node *node, int fd);

int		export_name(char *export, t_var *envp);

int		cd(t_var *envp, char *dir, int fd);

int		echo_fst(char *str, int fd);

int		pwd(int fd);

int		export_print(t_var *envp, int fd);

void	init_node_num(t_node *node);

void	check_args(t_executor *executor, t_node *node);

void	init_executor(t_executor *executor, t_var *envp, t_node *node);

void	heredoc_handler(t_executor *executor, t_node *node_tmp, t_var *envp);

void	fd_manager_input(t_node *node, t_executor *executor);

void	fd_manager_output(t_node *node, t_executor	*executor);

char	**restore_envp(t_var *envp);

void	close_until_nn(t_executor *executor, int nn);

void	cmd_not_found(char *str, t_executor	*executor);

void	fd_manager(t_node *node, t_executor	*executor);

void	execve_error(char **re, t_node* node);

#endif
