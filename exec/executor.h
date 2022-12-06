/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 13:19:47 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/06 17:59:36 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>
# include <limits.h>


typedef struct s_call{
	t_node			*node;
	struct s_call 	*next;
}				t_call;

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
	int		child_processes;
	struct s_call	*cs;

}				t_exec;



int	builtin_caller(t_node *node, t_exec *executor, t_var *envp);

int	execution_manager (t_node *node, t_var *envp);

#endif