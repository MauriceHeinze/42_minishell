/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_funct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:40:12 by rpohl             #+#    #+#             */
/*   Updated: 2022/10/19 11:24:24 by rpohl            ###   ########.fr       */
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
			exit_msg("Pipe error", EXIT_FAILURE);
		i++;
	}
}

void	dup2_processor(int out, int in, int exit_code)
{
	if (dup2(out, in) < 0 && exit_code == 1)
		exit_msg("Dup 2 output - bad fd", EXIT_FAILURE);
	if (dup2(out, in) < 0 && exit_code == 0)
	{
		// dprintf(2, "<out %d - in %d>\n", out, in);
		perror("Dup 2 input - bad fd");
	}
	if (dup2(out, in) < 0 && exit_code == 2)
		exit(EXIT_FAILURE);
}

void	dup2_close_other(t_executor *executor, int pid,t_node *node)
{
	dprintf(2, "<out %d - in %d - pid %d - num_proc %d>\n", node->fd_out, node->fd_in, pid, executor->num_processes);
	if (pid == 1)
	{
		dup2_processor(node->fd_out, 1, 1);
		close_other_fd(executor, pid, pid);
		dup2_processor(node->fd_in, 0, 2);
		// if (pid != node->fd_out && pid != node->fd_in)
		// 	close(pid);
	}
	if (pid > 1 && pid < executor->num_processes)
	{
		dup2_processor(node->fd_in, 0, 0);
		close_other_fd(executor, (pid - 2) * 2, (pid) * 2 - 1);
		dup2_processor(node->fd_out, 1, 1);
		if ((pid - 2) * 2 != node->fd_in)
			close((pid - 2) * 2);
		if (pid * 2 - 1 != node->fd_out)
			close(pid * 2 - 1);
	}
	if (pid == executor->num_processes)
	{
		dup2_processor(node->fd_out, 1, 2);
		close_other_fd(executor, (pid - 2) * 2, (pid - 2) * 2);
		dup2_processor(node->fd_in, 0, 0);
		// if ((pid - 2) * 2 != node->fd_out && (pid - 2) * 2 != node->fd_in)
		// 	close((pid - 2) * 2);
	}
}

void	here_doc_open(t_executor *executor)
{
	executor->fd1 = open(".heredoc_tmp", O_RDONLY);
	if (executor->fd1 < 0)
	{
		unlink(".heredoc_tmp");
		perror("Read heredoc failed");
	}
}

// void	here_doc(char *argv, t_executor *executor)
// {
// 	int		file;
// 	char	*buffer;

// 	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
// 	if (file < 0)
// 	{
// 		perror("heredoc tempfile error");
// 		return ;
// 	}
// 	while (1 && file > 0)
// 	{
// 		write(1, "heredoc> ", 9);
// 		buffer = get_next_line(0);
// 		if (buffer == NULL)
// 			exit_msg("GNL Error", EXIT_FAILURE);
// 		if (!ft_strncmp(argv, buffer, ft_strlen(argv)))
// 			break ;
// 		write(file, buffer, ft_strlen(buffer));
// 		free(buffer);
// 	}
// 	free(buffer);
// 	close(file);
// 	here_doc_open(executor);
// }
