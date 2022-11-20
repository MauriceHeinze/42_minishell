/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:33:17 by rpohl             #+#    #+#             */
/*   Updated: 2022/11/20 15:22:14 by mheinze          ###   ########.fr       */
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
int	echo(char *str, int fd)
{
	char	*check;
	int		quotes;
	// Should be devioded into in signel and in double quotes
	int		inside_single_quotes;
	int		inside_double_quotes;
	int		n;
	int		num_n;

	check = str;
	quotes = 0;
	n = 0;
	num_n = 0;
	inside_single_quotes = 0;
	inside_double_quotes = 0;
	if (str == NULL)
		return (EXIT_SUCCESS);
	while ((ft_strncmp(&(str[num_n]), "-", 1) == 0))
	{
		num_n += 1;
		if((ft_strncmp(&(str[num_n]), "n", 1) != 0))
			break;
		while ((ft_strncmp(&(str[num_n]), "n", 1) == 0))
			num_n += 1;
		if((ft_strncmp(&(str[num_n]), ";", 1) != 0))
			break;
		else
		{
			str += num_n;
			num_n = 0;
			n = 1;
		}
	}
	while (*str != '\0')
	{
		if (*str == '\"' && !inside_single_quotes)
		{
			if (inside_double_quotes)
				inside_double_quotes = 0;
			else if (!inside_double_quotes)
				inside_double_quotes = 1;
			str++;
		}
		else if (!inside_double_quotes && *str == '\'')
		{
			if (inside_single_quotes)
				inside_single_quotes = 0;
			else if (!inside_single_quotes)
				inside_single_quotes = 1;
			str++;
		}
		else if (*str == ';' && !inside_single_quotes && !inside_double_quotes)
		{
			str++;
			write(fd, " ", 1);
		}
		else
			write(fd, str++, 1);
	}
	if (!n)
		write(fd, "\n", 1);
	return(EXIT_SUCCESS);
}

// What about variables like $USER?
// change working relative or aboslute
// Relative paths can use . to stay in the current dir and .. to go one dir up
// WHat error management is needed? e.g. dir not found
// does stringcompare recognize the null temrinator int the string? This is a must
int	cd(t_var *envp, char *dir)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("getcwd failed");
		return (EXIT_FAILURE);
	}

	if (dir == NULL || *dir == '\0')
	{
		if (chdir (get_env(envp, "HOME")) == -1)
		{
			perror("chdir failed");
			return(EXIT_FAILURE);
		}
	}
	else
	{
		if (chdir (dir) == -1)
		{
			perror("chdir failed");
			return(EXIT_FAILURE);
		}
	}
	if (add_env(envp, "OLDPWD", cwd) == NULL)
		perror("add_env failed");
	if (getcwd(cwd, PATH_MAX) == NULL)
		perror("getcwd failed");
	if (add_env(envp, "PWD", cwd) == NULL)
		perror("add_env failed");
	return (EXIT_SUCCESS);
}

// Print the full filename of the current working directory.
int	pwd(int fd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("getcwd failed");
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(cwd, fd, NULL);
	write(fd, "\n", 1);
	return (EXIT_SUCCESS);
}

int	export(char *export, t_var *envp)
{
	int		length_name;
	int		length_content;
	char	*name;
	char	*content;

	length_content = 0;
	length_name = 0;
	if (export == NULL)
		return (EXIT_SUCCESS);
	if (!((*export >= 'A' && *export <= 'Z') || (*export >= 'a' && *export <= 'z')))
	{
		perror("Not a valid identifier");
		return (EXIT_FAILURE);
	}
	while(export[length_name] != '\0' && export[length_name] != '=')
		length_name++;
	if (export[length_name] != '\0' && export[length_name] != '=')
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
	return (EXIT_SUCCESS);
}

int	unset(char *remove, t_var *envp)
{
	remove_env(envp, remove);
	return (EXIT_SUCCESS);
}

int	env(t_var *envp, int fd)
{
	t_var	*temp;

	temp = envp;
	while(temp != NULL)
	{
		write(fd, temp->not_splitted, ft_strlen(temp->not_splitted));
		write(fd, "\n", 1);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

int	builtin_caller(t_node *node, t_exec *executor, t_var *envp)
{
	if (ft_strncmp(node->full_cmd, "cd", ft_strlen("cd")) == 0)
		executor->status = cd(envp, &(node->full_cmd[ft_strlen("cd") + 3]));
	else if (ft_strncmp(node->full_cmd, "echo", ft_strlen("echo")) == 0)
		executor->status = echo(&(node->full_cmd[ft_strlen("echo") + 3]), executor->fd_out);
	else if (ft_strncmp(node->full_cmd, "pwd", ft_strlen("pwd")) == 0)
		executor->status = pwd(executor->fd_out);
	else if (ft_strncmp(node->full_cmd, "export", ft_strlen("export")) == 0)
		executor->status = export(&(node->full_cmd[ft_strlen("export") + 3]), envp);
	else if (ft_strncmp(node->full_cmd, "unset", ft_strlen("unset")) == 0)
		executor->status = unset(&(node->full_cmd[ft_strlen("unset") + 3]), envp);
	else if (ft_strncmp(node->full_cmd, "env", ft_strlen("env")) == 0)
		executor->status = env(envp, executor->fd_out);
	else if (ft_strncmp(node->full_cmd, "exit", ft_strlen("exit")) == 0)
		exit(0);
	else
	{
		perror("builtin not found");
		executor->status = 1;
	}
	if (executor->fd_out != 1 && executor->fd_out != 2 && executor->fd_out != 0)
		close(executor->fd_out);
	return (executor->status);
}
