/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:49:49 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/11 14:08:04 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	child_process(t_executor *ex, int pid, t_var *envp, t_node *node)
{
	char	**args;
	char	**re;

	re = restore_envp(envp);
	args = ft_split(node->full_cmd_orig, ' ');
	dup2_close_other(ex, pid, node);
	if (execve(get_cmd_path(ex->cmd_paths, *args), args, re) == -1)
	{
		exec_error(CMD_NOT_FOUND, *args);
		free_double_ptr(re, 1);
		free_double_ptr(args, 1);
		close(node->fd_out);
		close(node->fd_in);
		set_exit_code(127);
	}
	return (0);
}

void	prepare_child_process(t_executor *executor,
t_var *envp, t_node *node, int x)
{
	executor->pids[x] = fork();
	if (executor->pids[x] == -1)
		exec_error(FORK_ERROR, NULL);
	if (executor->pids[x] == 0)
	{
		fd_manager_output(node, executor);
		fd_manager_input(node, executor);
		child_process(executor, x + 1, envp, node);
	}
}

static void	fork_processes(t_executor *executor, t_var *envp, t_node *node)
{
	int		x;

	x = 0;
	while (node != NULL)
	{
		if (node->full_path == NULL && node->full_cmd == NULL
			&& node->full_cmd_orig == NULL)
		{
			fd_manager_output(node, executor);
			fd_manager_input(node, executor);
		}
		if (ft_strcmp(node->full_path, "builtin") != 0)
			prepare_child_process(executor, envp, node, x);
		else if (ft_strcmp(node->full_path, "builtin") == 0)
		{
			fd_manager_output(node, executor);
			fd_manager_input(node, executor);
			builtin_caller(node, executor, envp);
		}
		x++;
		node = node->next;
	}
}

int	executor(t_node *node, t_var *envp)
{
	t_executor	executor;
	int			i;

	i = 0;
	init_node_num(node);
	check_args (&executor, node);
	init_executor (&executor, envp, node);
	create_pipes(&executor);
	heredoc_handler(&executor, node, envp);
	fork_processes(&executor, envp, node);
	while (i < executor.num_processes)
		waitpid(executor.pids[i++], &(executor.status), 0);
	if (!WIFSIGNALED(executor.status))
		set_exit_code(WEXITSTATUS(executor.status));
	else if (WIFSIGNALED(executor.status))
		set_exit_code(WTERMSIG(executor.status) + 128);
	close_other_fd(&executor, -1, -1);
	if (executor.num_pipes > 0)
		free(executor.pipes);
	free(executor.pids);
	free_double_ptr(executor.cmd_paths, 0);
	return (0);
}
