/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:49:49 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/16 18:51:12 by rpohl            ###   ########.fr       */
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
		free_double_ptr(re);
		free_double_ptr(args);
		close(node->fd_out);
		close(node->fd_in);
		set_exit_code(127);
	}
	return (0);
}

void	prepare_child_process(t_executor *executor,
t_var *envp, t_node *node, int x)
{
	child_signal_handler();
	executor->pids[x] = fork();
	if (executor->pids[x] == -1)
		exec_error(FORK_ERROR, NULL);
	if (executor->pids[x] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		fd_manager_output(node, executor);
		fd_manager_input(node, executor);
		child_process(executor, x + 1, envp, node);
	}
	else
		close_until_nn(executor, (node->node_num - 1));
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
		else if (ft_strcmp(node->full_path, "builtin") != 0)
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

static void	free_executor(t_executor *executor)
{
	if (executor->num_pipes > 0)
		free(executor->pipes);
	free(executor->pids);
	if (executor->cmd_paths != NULL)
		free_double_ptr(executor->cmd_paths);
}

int	executor(t_node *node, t_var *envp)
{
	t_executor	executor;

	init_node_num(node);
	check_args (&executor, node);
	init_executor (&executor, envp, node);
	create_pipes(&executor);
	heredoc_handler(&executor, node, envp);
	fork_processes(&executor, envp, node);
	while(waitpid(-1, &(executor.status), 0) != -1)
		continue;
	if (executor.status < 0)
		set_exit_code(1);
	else if (!WIFSIGNALED(executor.status))
		set_exit_code(WEXITSTATUS(executor.status));
	else if (WIFSIGNALED(executor.status))
		set_exit_code(WTERMSIG(executor.status) + 128);
	close_other_fd(&executor, -1, -1);
	free_executor(&executor);
	return (0);
}
