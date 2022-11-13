/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:33:17 by rpohl             #+#    #+#             */
/*   Updated: 2022/11/13 14:29:54 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// How much error handling is required for the buildins?
// Best Guess: The error messages are in the builtin
// What are the different error cases?
#include "../inc/minishell.h"
#include "executor.h"

// Echo the STRING(str) to standard output.
// If n is true do not output the trailing newline
// If str is empty printf nothing an do not throw error
void	echo(char *str)
{
	int	n;

	n = 0;
	if (ft_strncmp(str, "-n ", ft_strlen("-n ")) == 0)
		n = 1;
	if (str != NULL)
	{
		while (*str != '\0')
			write(1, str++, 1);
	}
	if (n != 1)
		write(1, "\n", 1);
}

// What about variables like $USER?
// change working relative or aboslute
// Relative paths can use . to stay in the current dir and .. to go one dir up
// WHat error management is needed? e.g. dir not found
// does stringcompare recognize the null temrinator int the string? This is a must 
void	cd(char *dir)
{
	if (chdir (dir) == -1)
		perror("chdir failed");
}

// Print the full filename of the current working directory.
void	pwd()
{
	char	*cwd;
	
	if (getcwd(cwd, 0) == NULL)
		perror("getcwd failed");
	ft_putstr_fd(cwd, 1, NULL);
	free(cwd);
}

void	export(char *export, t_var *envp)
{
	int		i;
	t_var	*new_var;
	t_var	*lst_envp;

	i = 0;
	lst_envp = envp;
	while (export[i] != '=')
	{
		if (export[i++] == '\0')
			perror("No = found in export");
	}
	while (lst_envp->next != NULL)
		lst_envp = lst_envp->next;
	new_var = setup_var_node();
	lst_envp->next = new_var;
	// new_var->name 
	// new_var->content
	// new_var->"complete"	
}



// void	env(t_var *envp)
// {
// 	t_var	*temp;

// 	temp = envp;
// 	while(temp != NULL)
// 	{
// 		write(1, envp->"complete", ft_strlen(envp->"complete"));
// 		temp = temp->next;
// 	}
// }

void	builtin_caller(t_node *node, t_var *envp)
{
	if (ft_strncmp(node->full_cmd, "cd", ft_strlen("cd")) == 0)
		cd(&(node->full_cmd[ft_strlen("cd") + 2]));
	if (ft_strncmp(node->full_cmd, "echo", ft_strlen("echo")) == 0)
		echo(&(node->full_cmd[ft_strlen("echo") + 2]));
	if (ft_strncmp(node->full_cmd, "pwd", ft_strlen("pwd")) == 0)
		pwd();
	if (ft_strncmp(node->full_cmd, "export", ft_strlen("export")) == 0)
		export(&(node->full_cmd[ft_strlen("export") + 2]), envp);
	// if (ft_strncmp(node->full_cmd, "unset", ft_strlen("unset")) == 0)
	// 	unset(&(node->full_cmd[ft_strlen("unset") + 2]), envp);
	// if (ft_strncmp(node->full_cmd, "env", ft_strlen("env")) == 0)
	// 	env(envp);
	if (ft_strncmp(node->full_cmd, "pwd", ft_strlen("pwd")) == 0)
		dprintf(2, "EXIT");// exit();
}
