/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/06 14:18:26 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_fds(t_node *node)
{
	t_fd	*fd;
	t_fd	*tmp_fd;

	fd = node->fd;
	while (fd != NULL)
	{
		tmp_fd = fd;
		fd = fd->next;
		free(tmp_fd->meta);
		tmp_fd->meta = NULL;
		free(tmp_fd);
	}
}

void	free_nodes(void)
{
	t_node	*node;
	t_node	*tmp_node;

	node = program->nodes;
	while (node != NULL)
	{
		tmp_node = node;
		node = node->next;
		free_fds(tmp_node);
		free(tmp_node->full_cmd);
		tmp_node->full_cmd = NULL;
		free(tmp_node->full_cmd_orig);
		tmp_node->full_cmd_orig = NULL;
		if (ft_strcmp(tmp_node->full_path, "builtin"))
		{
			free(tmp_node->full_path);
			tmp_node->full_path = NULL;
		}
		free(tmp_node);
	}
}
