/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralf <ralf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 13:19:47 by rpohl             #+#    #+#             */
/*   Updated: 2022/11/23 17:23:48 by ralf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>
# include <limits.h>

typedef struct s_exec {
	int		pipe[2];
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

}				t_exec;

int	builtin_caller(t_node *node, t_exec *executor, t_var *envp);

int	execution_manager (t_node *node, t_var *envp);

#endif