/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralf <ralf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:33:17 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/01 17:16:54 by ralf             ###   ########.fr       */
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
// Input: echo "'"Halli"'" "'" Hallo "'" Sowieso
// Output: ;Halli;" ;" ;Hallo ;" ;Sowieso
// Full cmd: echo;"'";Halli;"'" ;"'" ;Hallo ;"'" ;Sowieso
int	echo(char *str, int fd)
{
	char	*check;
	int		quotes;
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
		if((ft_strncmp(&(str[num_n]), " ;", 2) != 0))
			break;
		else
		{
			str += 2;
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
			str++;
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
	if (add_env(envp, ft_strdup("OLDPWD"), ft_strdup(cwd)) == NULL)
		perror("add_env failed");
	if (getcwd(cwd, PATH_MAX) == NULL)
		perror("getcwd failed");
	if (add_env(envp, ft_strdup("PWD"), ft_strdup(cwd)) == NULL)
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

int	exit_pre_handler(t_node *node, int fd)
{
	char	*check_input;
	
	if (ft_strlen("exit") == ft_strlen(node->full_cmd))
	{
		exit_shell(0);
		ft_putstr_fd("exit\n", fd, NULL);	
	}
	else
	{
		check_input = &(node->full_cmd[ft_strlen("exit") + 1]);
		if (*check_input == '+' || *check_input == '-')
			check_input++;
		while (*check_input != '\0')
		{
			if (*check_input >= '0' && *check_input <= '9')
				check_input++;
			else
			{
				ft_putstr_fd("exit\n", fd, NULL);
				if (*check_input == ' ')
				{
					exec_error(EXIT_NUM_ERROR, &(node->full_cmd[ft_strlen("exit") + 1]));
					return (1);
				}
				exec_error(EXIT_ARG_ERROR, &(node->full_cmd[ft_strlen("exit") + 1]));
				exit_shell(255);
			}
		}
		ft_putstr_fd("exit\n", fd, NULL);
		exit_shell(ft_atoi(&(node->full_cmd[ft_strlen("exit") + 1])));
	}
	return(0);
}


int	builtin_caller(t_node *node, t_exec *executor, t_var *envp)
{
	// TEST ONLY!!!
	// if (executor->fd_out == 1)
	// 	executor->fd_out = 2;
	
	if (ft_strncmp(node->full_cmd, "cd", ft_strlen("cd")) == 0)
		executor->status = cd(envp, &(node->full_cmd[ft_strlen("cd") + 1]));
	else if (ft_strncmp(node->full_cmd, "echo", ft_strlen("echo")) == 0)
		executor->status = echo(&(node->full_cmd[ft_strlen("echo") + 1]), executor->fd_out);
	else if (ft_strncmp(node->full_cmd, "pwd", ft_strlen("pwd")) == 0)
		executor->status = pwd(executor->fd_out);
	else if (ft_strncmp(node->full_cmd, "export", ft_strlen("export")) == 0)
		executor->status = export(&(node->full_cmd[ft_strlen("export") + 1]), envp);
	else if (ft_strncmp(node->full_cmd, "unset", ft_strlen("unset")) == 0)
		executor->status = unset(&(node->full_cmd[ft_strlen("unset") + 1]), envp);
	else if (ft_strncmp(node->full_cmd, "env", ft_strlen("env")) == 0)
		executor->status = env(envp, executor->fd_out);
	else if (ft_strncmp(node->full_cmd, "exit", ft_strlen("exit")) == 0)
		executor->status = exit_pre_handler(node, executor->fd_out);
	else
	{
		perror("builtin not found");
		executor->status = 1;
	}
	if (!(executor->fd_out == 1))
	{
		if (executor->fd_out == executor->pipe[1])
		{
			// close(executor->fd_out);
			if(dup2(executor->fd_out_original, 1) < 0)
				perror("Dup 2 restore output error");
			close(executor->fd_out_original);
			executor->fd_out = 1;
			executor->fd_out_original = dup(1);
		}
		else
		{
			close(executor->fd_out);
			executor->fd_out = 1;
		}
	}
	if (!(executor->fd_in == 0))
	{
		if (executor->fd_in == executor->pipe[0])
		{
			// close(executor->fd_in);
			if(dup2(executor->fd_in_original, 0) < 0)
				perror("Dup 2 restore output error");
			close(executor->fd_in_original);
			executor->fd_in = 0;
			executor->fd_in_original = dup(0);
			// if (pipe(executor->pipe) < 0)
			// 	perror("Pipe error");
		}
		else
		{
			close(executor->fd_in);
			executor->fd_in = 0;
		}
	}
	return (executor->status);
}