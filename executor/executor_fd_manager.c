/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_fd_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:04:10 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/11 14:04:16 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	oi(char *meta, int mode, int heredoc)
{
	int	fd;

	fd = 1;
	if (mode == MODE_FILE)
	{
		fd = open(meta, O_RDONLY);
		if (fd == -1)
			exec_error(PATH_ERROR, meta);
	}
	else if (mode == MODE_HEREDOC)
		fd = heredoc;
	return (fd);
}

void	fd_manager_input(t_node *node, t_executor *executor)
{
	t_fd	*fd_temp;
	t_fd	*fd_former;

	if (executor == NULL || node == NULL)
		return ;
	node->fd_in = 0;
	fd_temp = node->fd;
	fd_former = NULL;
	while (fd_temp != NULL)
	{
		if (fd_temp->io == 0)
			fd_temp = fd_temp->next;
		else
		{
			node->fd_in_found = 1;
			fd_temp->fd = oi(fd_temp->meta, fd_temp->mode, executor->heredoc);
			if (fd_former != NULL)
				close(fd_former->fd);
			fd_former = fd_temp;
			node->fd_in = fd_temp->fd;
			fd_temp = fd_temp->next;
		}
	}
	if (node->fd_in_found == 0 && node != executor->first_node)
		node->fd_in = executor->pipes[(node->node_num - 1) * 2];
}

static int	oo(char *meta, int mode)
{
	int	fd;

	fd = 1;
	if (mode == MODE_FILE)
		fd = open(meta, O_TRUNC | O_CREAT | O_RDWR, 000644);
	else if (mode == MODE_APPEND)
		fd = open(meta, O_APPEND | O_CREAT | O_RDWR, 000644);
	if (fd == -1)
		exec_error(PERMISSION_ERROR, meta);
	return (fd);
}

void	fd_manager_output(t_node *node, t_executor	*executor)
{
	t_fd	*fd_temp;
	t_fd	*fd_former;

	if (executor == NULL || node == NULL)
		return ;
	node->fd_out = 1;
	fd_temp = node->fd;
	fd_former = NULL;
	while (fd_temp != NULL)
	{
		if (fd_temp->io == 1)
			fd_temp = fd_temp->next;
		else
		{
			node->fd_out_found = 1;
			fd_temp->fd = oo(fd_temp->meta, fd_temp->mode);
			if (fd_former != NULL)
				close(fd_former->fd);
			fd_former = fd_temp;
			node->fd_out = fd_temp->fd;
			fd_temp = fd_temp->next;
		}
	}
	if (node->fd_out_found == 0 && node->next != NULL)
		node->fd_out = executor->pipes[node->node_num * 2 + 1];
}
