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
char	**get_cmd_paths(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	*envp += 5;
	return (ft_split(*envp, ':'));
}

// int main(int argc, char *argv[], char *envp[])
// {
// 	printf("%s\n", get_cmd_path(get_cmd_paths(envp), "echo"));
// 	return (0);
// }