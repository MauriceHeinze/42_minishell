/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_funct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:40:12 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/11 17:53:26 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	create_pipes(t_executor *executor)
{
	int	*pipe_temp;
	int	i;

	i = 0;
	while (i < executor->num_pipes)
	{
		pipe_temp = executor->pipes + 2 * i;
		if (pipe(pipe_temp) < 0)
			exec_error(PIPE_ERROR, NULL);
		i++;
	}
}

void	dup2_processor(int out, int in, int exit_code)
{
	if (dup2(out, in) < 0 && exit_code == 1)
		exec_error(DUP_ERROR, "output");
	if (dup2(out, in) < 0 && exit_code == 0)
		exec_error(DUP_ERROR, "input");
	if (dup2(out, in) < 0 && exit_code == 2)
		exit(EXIT_FAILURE);
}

void	dup2_middle_processor(t_executor *ex, int pid, t_node *node)
{
	dup2_processor(node->fd_in, 0, 0);
	close_other_fd(ex, (pid - 2) * 2, (pid) * 2 - 1);
	dup2_processor(node->fd_out, 1, 1);
	if (ex->pipes[(pid - 2 * 2)] != node->fd_in)
		close(ex->pipes[(pid - 2 * 2)]);
	if (ex->pipes[(pid * 2 - 1)] != node->fd_out)
		close(ex->pipes[(pid * 2 - 1)]);
}

void	dup2_close_other(t_executor *ex, int pid, t_node *node)
{
	if (pid == 1)
	{
		dup2_processor(node->fd_out, 1, 1);
		close_other_fd(ex, pid, pid);
		dup2_processor(node->fd_in, 0, 2);
		if (ex->num_pipes > 0 && (ex->pipes[pid] != node->fd_out
				&& ex->pipes[pid] != node->fd_in))
			close(pid);
	}
	if (pid > 1 && pid < ex->num_processes)
		dup2_middle_processor(ex, pid, node);
	if (pid == ex->num_processes && ex->num_processes > 1)
	{
		dup2_processor(node->fd_out, 1, 2);
		close_other_fd(ex, (pid - 2) * 2, (pid - 2) * 2);
		dup2_processor(node->fd_in, 0, 0);
		if (ex->pipes[(pid - 2)] * 2 != node->fd_out
			&& ex->pipes[(pid - 2)] != node->fd_in)
			close(ex->pipes[(pid - 2)]);
	}
}
