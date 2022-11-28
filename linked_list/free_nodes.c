/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/11/28 20:28:24 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char				*full_cmd; // e.g. echo, cd etc.
// char				*full_path; // if builtin, then it's just full_cmd, else it's path to that cmd
// int				pid; // default -1, is set by executor
// int				infile_mode; // 1. file -> full path, 2. heredoc -> delimiter, 3. stdin -> nothing 4. pipe
// char				*infile_meta; // full path name || delimiter | NULL || pipe id
// int				outfile_mode; // 1. file -> full path, 2. heredoc -> delimiter, 3. stdin -> nothing 4. pipe
// char				*outfile_meta; // full path name || delimiter || pipe id

// < redirection fd ist nicht stdin, sondern fd
// > redirection fd ist nicht stdout, sondern fd
// << redirection fd ist nicht stdin, sondern heredoc
// >> output ist in appendmode -> cat text >> cat text1
// check pipex manual

static void	free_fds(t_node *node)
{
	t_fd *fd;
	t_fd *tmp_fd;

	while (fd != NULL)
	{
		fd = node->fd;
		tmp_fd = fd->next;
		free(fd);
		fd = tmp_fd;
	}
}

void	free_nodes(void)
{
	t_node *node;
	t_node *tmp_node;

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