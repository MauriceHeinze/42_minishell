/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/14 18:25:17 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_cmd_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		tmp = NULL;
		if (access(command, X_OK) == 0)
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

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (cmd[0] != '.')
	{
		while (paths != NULL && *paths)
		{
			tmp = ft_strjoin(*paths, "/");
			command = ft_strjoin(tmp, cmd);
			free(tmp);
			tmp = NULL;
			if (access(command, X_OK) == 0)
				return (command);
			free(command);
			command = NULL;
			paths++;
		}
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
