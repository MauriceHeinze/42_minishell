/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fd_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2023/01/13 18:08:56 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	node_null(t_node **node, t_fd **head, t_fd **fd)
{
	if ((*node)->fd != NULL)
	{
		*fd = (*node)->fd;
		*head = *fd;
		while ((*fd)->next != NULL)
			*fd = (*fd)->next;
		(*fd)->next = setup_fd();
		(*fd) = (*fd)->next;
		*head = *fd;
	}
	else
	{
		(*node)->fd = setup_fd();
		*fd = (*node)->fd;
		*head = *fd;
	}
}

void	free_multiple(char *a, char *b, char *c, char *d)
{
	free(a);
	a = NULL;
	free(b);
	b = NULL;
	free(c);
	c = NULL;
	free(d);
	d = NULL;
}
