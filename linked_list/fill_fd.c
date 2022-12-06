/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/06 20:43:06 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	fill_fd(t_program *program, t_node *node, int *pos)
{
	t_fd	*fd;
	t_fd	*head;
	int		category;
	char	*tmp;

	category = get_category(program->tokens[(*pos)]);
	if (category == ARROW_RIGHT || category == ARROW_LEFT
		|| category == DOUBLE_ARROW_RIGHT || category == DOUBLE_ARROW_LEFT)
	{
		if (!program->tokens[(*pos + 1)])
			return (0);
	}
	if (node->fd != NULL)
	{
		fd = node->fd;
		head = fd;
		while (fd->next != NULL)
			fd = fd->next;
	}
	node->fd = setup_fd();
	fd = node->fd;
	head = fd;
	fd_handle_redirection(category, node, fd, pos);
	fd = head;
	return (1);
}
