/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:44:02 by rpohl             #+#    #+#             */
/*   Updated: 2022/10/18 18:19:19 by rpohl            ###   ########.fr       */
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
	close(executor->fd1);
	close(executor->fd2);
}

// char	*get_cmd_path(char **paths, char *cmd)
// {
// 	char	*tmp;
// 	char	*command;

// 	if (access(cmd, 0) == 0)
// 		return (cmd);
// 	while (*paths)
// 	{
// 		tmp = ft_strjoin(*paths, "/");
// 		command = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		if (access(command, 0) == 0)
// 			return (command);
// 		free(command);
// 		paths++;
// 	}
// 	return (NULL);
// }

// char	**get_cmd_paths(t_var *envp)
// {
// 	char	**paths;
// 	t_var	*tmp;

// 	tmp = envp;
// 	while (ft_strcmp("PATH", tmp->name) != 0)
// 		tmp = tmp->next;
// 	paths = ft_split(tmp->content, ':');
// 	return (paths);
// }

char	exit_msg(char *msg, char exit_code)
{
	perror(msg);
	exit(exit_code);
}
