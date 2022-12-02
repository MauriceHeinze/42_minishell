/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralf <ralf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 13:19:47 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/02 17:59:25 by ralf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>
# include <limits.h>

typedef struct s_exec {
	int		pipe1[2];
	int		pipe2[2];
	int		*pipe_ptr;
	pid_t	*pids;
	int		status;
	int		heredoc;
	char	*limiter;
	int		pipes;
	pid_t	pid_old;
	t_node	*first_node;
	int		fd_out;
	int		fd_in;
	int		fd_out_original;
	int		fd_in_original;
	int		child_processes;

}				t_exec;

int	builtin_caller(t_node *node, t_exec *executor, t_var *envp);

int	execution_manager (t_node *node, t_var *envp);

#endif