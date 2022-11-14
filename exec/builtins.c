/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:33:17 by rpohl             #+#    #+#             */
/*   Updated: 2022/11/14 18:01:12 by rpohl            ###   ########.fr       */
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
// Example "echo ; -n ; -n ; 1 2  3 ; 1 ; 2 ; 3"
void	echo(char *str)
{
	char	*check;
	int		quotes;
	int		inside_quotes;
	int		n;
	
	check = str;
	quotes = 0;
	n = 0;
	inside_quotes = 0;
	while (*check != '\0')
	{
		if (*check == '\"')
			quotes += 1;
		check++;
	}
	if (quotes%2 > 0)
		perror("Uneven quotes");
	while ((ft_strncmp(str, "-n ; ", 5) == 0))
	{
		str += 5;
		n = 1;
	}
	while (*str != '\0')
	{
		if (*str == '\"')
		{
			if (inside_quotes)
				inside_quotes = 0;
			if (!inside_quotes)
				inside_quotes = 1;
			str++;
		}
		else if (*str == ';' && !inside_quotes)
			str += 2;
		else
			write(1, str++, 1);
	}
	if (!n)
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
	char	cwd[PATH_MAX];
	
	if (getcwd(cwd, PATH_MAX) == NULL)
		perror("getcwd failed");
	ft_putstr_fd(cwd, 1, NULL);
	write(1, "\n", 1);
}

void	export(char *export, t_var *envp)
{
	int		length_name;
	int		length_content;
	char	*name;
	char	*content;
	
	length_content = 0;
	length_name = 0;
	while(export[length_name] != '\0' && export[length_name] != '=')
		length_name++;
	if (export[length_name] != '=')
		perror("Bad assignment");
	name = malloc(sizeof(char) * (length_name + 1));
	ft_strlcpy(name, export, length_name + 1);
	name[length_name] = '\0';
	while(export[length_name + 1 + length_content] != '\0')
		length_content++;
	content = malloc(sizeof(char) * (length_content + 1));
	ft_strlcpy(content, &export[length_name + 1], length_content + 1);
	content[length_content] = '\0';
	add_env(envp, name, content);
}

void	unset(char *remove, t_var *envp)
{
	remove_env(envp, remove);
}

void	env(t_var *envp)
{
	t_var	*temp;

	temp = envp;
	while(temp != NULL)
	{
		write(1, temp->not_splitted, ft_strlen(temp->not_splitted));
		write(1, "\n", 1);
		temp = temp->next;
	}
}

void	builtin_caller(t_node *node, t_var *envp)
{
	if (ft_strncmp(node->full_cmd, "cd", ft_strlen("cd")) == 0)
		cd(&(node->full_cmd[ft_strlen("cd") + 3]));
	else if (ft_strncmp(node->full_cmd, "echo", ft_strlen("echo")) == 0)
		echo(&(node->full_cmd[ft_strlen("echo") + 3]));
	else if (ft_strncmp(node->full_cmd, "pwd", ft_strlen("pwd")) == 0)
		pwd();
	else if (ft_strncmp(node->full_cmd, "export", ft_strlen("export")) == 0)
		export(&(node->full_cmd[ft_strlen("export") + 3]), envp);
	else if (ft_strncmp(node->full_cmd, "unset", ft_strlen("unset")) == 0)
		unset(&(node->full_cmd[ft_strlen("unset") + 3]), envp);
	else if (ft_strncmp(node->full_cmd, "env", ft_strlen("env")) == 0)
		env(envp);
	else if (ft_strncmp(node->full_cmd, "exit", ft_strlen("exit")) == 0)
		exit(0);
	else
		perror("builtin not found");
}
