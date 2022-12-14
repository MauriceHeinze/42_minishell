/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:44:02 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/14 18:32:30 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	close_until_nn(t_executor *executor, int nn)
{
	int	i;

	i = 0;
	while (i <= nn)
	{
		close(executor->pipes[i * 2]);
		close(executor->pipes[i * 2 + 1]);
		i++;
	}
}

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

char	**restore_envp(t_var *envp)
{
	char	**restored_envp;
	t_var	*temp;
	int		counter;
	int		i;

	if (envp == NULL)
		return (NULL);
	temp = envp;
	counter = 0;
	i = 0;
	while (temp != NULL)
	{
		counter++;
		temp = temp->next;
	}
	restored_envp = malloc(sizeof(char *) * (counter + 1));
	temp = envp;
	while (temp != NULL)
	{
		restored_envp[i] = temp->not_splitted;
		temp = temp->next;
		i++;
	}
	restored_envp[i] = NULL;
	return (restored_envp);
}
