/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:44:02 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/11 10:32:00 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	close_other_fd(t_executor *executor, int fd1, int fd2)
{
	int	i;

	i = 0;
	while (i < executor->num_pipes * 2)
	{
		if (!(i == fd1 || i == fd2))
			close(executor->pipes[i]);
		i++;
	}
}

void	close_fd(t_executor *executor)
{
	int	i;

	i = 0;
	while (i < executor->num_pipes)
	{
		close(executor->pipes[2 * i]);
		close(executor->pipes[2 * i + 1]);
		i++;
	}
}

char	exit_msg(char *msg, char exit_code)
{
	perror(msg);
	exit(exit_code);
}
