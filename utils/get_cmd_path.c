/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/11 22:44:56 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// returns path of executable
char	*get_cmd_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (access(cmd, 0) == 0)
		return (ft_strdup(cmd));
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		tmp = NULL;
		if (access(command, 0) == 0)
			return (command);
		free(command);
		command = NULL;
		paths++;
	}
	free(cmd);
	return (NULL);
}

char	*get_cmd_path_no_free(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (access(cmd, 0) == 0)
		return (ft_strdup(cmd));
	while (paths != NULL && *paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		tmp = NULL;
		if (access(command, 0) == 0)
			return (command);
		free(command);
		command = NULL;
		paths++;
	}
	g_program->unknown_cmd = ft_strdup(cmd);
	set_exit_code(127);
	return (NULL);
}

// returns executable paths
char	**get_cmd_paths(t_var *envp)
{
	char	**paths;
	t_var	*tmp;

	tmp = envp;
	while (tmp != NULL && (ft_strcmp("PATH", tmp->name) != 0))
		tmp = tmp->next;
	if (tmp == NULL)
		return (NULL);
	paths = ft_split(tmp->content, ':');
	return (paths);
}
