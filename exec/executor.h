/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 13:19:47 by rpohl             #+#    #+#             */
/*   Updated: 2022/11/13 18:19:47 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>

typedef struct s_exec {
	int		pipe[2];
	pid_t	*pids;
	int		status;
	int		heredoc;
	char	*limiter;
	int		pipes;
	pid_t	pid_old;
	t_node	*first_node;
	
}				t_exec;

void	builtin_caller(t_node *node, t_var *envp);

int		execution_manager (t_node *node, t_var *envp);

#endif