/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:05:47 by rpohl             #+#    #+#             */
/*   Updated: 2022/10/19 11:14:37 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef executor_BONUS_H
# define executor_BONUS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

#include "../inc/minishell.h"

typedef struct s_executor
{
	int		fd1;
	int		fd2;
	int		*pipes;
	int		num_pipes;
	int		num_processes;
	pid_t	*pids;
	char	*all_paths;
	char	**cmd_paths;
	char	**args;
	char	*limiter;
	char	*buffer;
	int		status;
	t_node	*first_node;
	int		fd_out_original;
	int		fd_in_original;
}	t_executor;

void	close_fd(t_executor *executor);

void	close_other_fd(t_executor *executor, int fd1, int fd2);

void	create_pipes(t_executor *executor);

void	dup2_close_other(t_executor *executor, int pid, t_node *node);

void	dup2_processor(int out, int in, int exit_code);

void	here_doc(char *argv, t_executor *executor);

void	here_doc_open(t_executor *executor);

char	*get_cmd_path(char **paths, char *cmd);

char	exit_msg(char *msg, char exit_code);

int	builtin_caller(t_node *node, t_executor *executor, t_var *envp);

int	executor (t_node *node, t_var *envp);

#endif