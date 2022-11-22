#include "../inc/minishell.h"

// returns path of executable
char	*get_cmd_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (access(cmd, 0) == 0)
		return (cmd);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

// returns executable paths
char	**get_cmd_paths(t_var *envp)
{
	char	**paths;
	t_var	*tmp;

	tmp = envp;
	while (ft_strcmp("PATH", tmp->name) != 0)
		tmp = tmp->next;
	// printf("Here! %s\n", tmp->name);
	paths = ft_split(tmp->content, ':');
	return (paths);
}
