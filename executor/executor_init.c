/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:00:13 by rpohl             #+#    #+#             */
/*   Updated: 2023/01/13 17:23:39 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	init_node_num(t_node *node)
{
	t_node	*node_tmp;
	int		i;

	if (node == NULL)
		return ;
	i = 0;
	node_tmp = node;
	while (node_tmp != NULL)
	{
		node_tmp->node_num = i++;
		node_tmp->fd_in_found = 0;
		node_tmp->fd_out_found = 0;
		node_tmp = node_tmp->next;
	}
}

void	check_args(t_executor *executor, t_node *node)
{
	t_node	*node_tmp;

	if (executor == NULL || node == NULL)
		return ;
	executor->num_processes = 0;
	executor->num_pipes = 0;
	node_tmp = node;
	while (node_tmp != NULL)
	{
		executor->num_processes += 1;
		node_tmp = node_tmp->next;
	}
	node_tmp = node;
	while (node_tmp->next != NULL)
	{
		executor->num_pipes += 1;
		node_tmp = node_tmp->next;
	}
}

void	init_executor(t_executor *executor, t_var *envp, t_node *node)
{
	if (executor->num_pipes > 0)
		executor->pipes = malloc(sizeof(int) * 2 * executor->num_pipes);
	executor->pids = malloc(sizeof(pid_t) * executor->num_processes);
	executor->cmd_paths = get_cmd_paths(envp);
	executor->status = 0;
	executor->first_node = node;
	executor->last_builtin_exit = -3;
}

static int	garbage_bin_2(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (errno == EACCES)
		{
			write(2, "minishell: ", 11);
			write(2, cmd, ft_strlen(cmd));
			write(2, ": is a directory\n", 17);
			return (2);
		}
		else if (errno == ENOENT)
			return (1);
	}
	return (0);
}

void	execve_error(char **re, t_node *node)
{
	int		err_code;

	(void) re;
	err_code = garbage_bin_2(node->full_path);
	if (err_code == 1)
	{
		write(2, "minishell: ", 11);
		write(2, node->full_path, ft_strlen(node->full_path));
		write(2, ": No such file or directory\n", 30);
	}
	else if (err_code == 0)
		exec_error(CMD_NOT_FOUND, ft_strdup(""));
	// exec_error(CMD_NOT_FOUND, ft_strdup(""));
	// free_dptr(re);
	close(node->fd_out);
	close(node->fd_in);
	set_exit_code(127);
}
