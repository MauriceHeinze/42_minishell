/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/11 21:37:36 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_fd	*setup_fd(void)
{
	t_fd	*fd;

	fd = malloc(sizeof(t_fd));
	if (!fd)
		return (NULL);
	fd->io = OUTPUT;
	fd->mode = -1;
	fd->meta = NULL;
	fd->fd = -1;
	fd->next = NULL;
	return (fd);
}
