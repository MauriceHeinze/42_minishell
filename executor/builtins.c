/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:33:17 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/09 14:34:36 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// How much error handling is required for the builtins?
// Best Guess: The error messages are in the builtin
// What are the different error cases?
#include "executor.h"
#include "../inc/minishell.h"
// Echo the STRING(str) to standard output.
// If n is true do not output the trailing newline
// If str is empty printf nothing an do not throw error
// Input: echo "'"Halli"'" "'" Hallo "'" Sowieso
// Output: ;Halli;" ;" ;Hallo ;" ;Sowieso
// Full cmd: echo;"'";Halli;"'" ;"'" ;Hallo ;"'" ;Sowieso
// Print the full filename of the current working directory.
int	pwd(int fd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("getcwd failed");
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(cwd, fd);
	write(fd, "\n", 1);
	return (EXIT_SUCCESS);
}

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
int	cd(t_var *envp, char *dir, int fd)
{
	char	**first_arg;
	char	cwd[PATH_MAX];

	first_arg = NULL;
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
	else if (ft_strcmp(dir, "-") == 0)
	{
		if (chdir (get_env(envp, "OLDPWD")) == -1)
		{
			perror("bash: cd: OLDPWD not set");
			return(EXIT_FAILURE);
		}
		pwd(fd);
	}
	else
	{
		first_arg = ft_split(dir, ' ');
		char **double_ptr = first_arg;
		if (chdir (*first_arg) == -1)
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
	if (first_arg != NULL)
	{
		char **double_ptr = first_arg;
		while(*first_arg != NULL)
			free(*first_arg++);
		free(double_ptr);
	}
	return (EXIT_SUCCESS);
}



char *export_content(char *export)
{
	int		length_content;
	char	*content;
	
	length_content = 0;
	if (export[length_content] == '\0' && export[length_content] == ' ' && export[length_content] == ';')
		perror("blala");
	while(export[length_content] != '\0' && export[length_content] != ' ' && export[length_content] != ';')
		length_content++;
	content = malloc(sizeof(char) * (length_content + 1));
	ft_strlcpy(content, export, length_content + 1);
	content[length_content] = '\0';
	return(content);	
}

int	export_print(t_var *envp, int fd)
{
	t_var	*temp;

	temp = envp;
	while(temp != NULL)
	{
		write(fd, "declare -x ", 11);
		write(fd, temp->name, ft_strlen(temp->name));
		if (temp->content != NULL)
		{
			write(fd, "=\"", 2);
			write(fd, temp->content, ft_strlen(temp->content));
			write(fd, "\"", 1);
		}
		write(fd, "\n", 1);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}


int	export_name(char *export, t_var *envp)
{
	int		length_name;
	char	*name;
	char	*content;
	
	content = NULL;
	if (!((*export >= 'A' && *export <= 'Z') || (*export >= 'a' && *export <= 'z')))
	{
		perror("EXPORT");
		return (EXIT_FAILURE);
	}
	else
	{		
		length_name = 0;
		while(export[length_name] != '\0' && export[length_name] != '=' && export[length_name] != ' ' && export[length_name] != ';')
			length_name++;
		name = malloc(sizeof(char) * (length_name + 1));
		ft_strlcpy(name, export, length_name + 1);
		name[length_name] = '\0';
		if (export[length_name] == '=')
			content = export_content(&(export[length_name + 1]));
		add_env(envp, name, content);
	}
	return (EXIT_SUCCESS);
}

int	length_until_semicolon (char *str)
{
	int	length;

	length = 0;
	while (str[length] != '\0' && str[length] != ';')
		length++;
	if (str[length] == ';')
		length++;
	return (length);
}

int	export_handler(char *export, t_var *envp, int fd)
{
	int 	exit_code;

	exit_code = 0;
	if (export == NULL)
		return (exit_code);
	else if (*export == '\0')
		export_print(envp, fd);
	else
	{
		while (*export != '\0')
		{
			if (exit_code == 0)
				exit_code = export_name(export, envp);
			else
				export_name(export, envp);
			export = export + length_until_semicolon(export);
		}	
	}
	return (exit_code);
}



int	unset(char *remove, t_var *envp)
{
	char	**remove_split;
	int		i;
	int		c;
	
	if(remove == NULL)
		return (EXIT_SUCCESS);
	i = 0;
	remove_split = ft_split(remove, ';');
	while(remove_split[i] != NULL)
	{
		c = 0;
		while(remove_split[i][c] != '\0')
		{
			if (remove_split[i][c] == ' ')
				remove_split[i][c] = '\0';
			c++;
		}
		remove_env(envp, remove_split[i++]);
	}
	while(i >= 0)
		free(remove_split[i--]);
	free(remove_split);
	return (EXIT_SUCCESS);
}

int	env(t_var *envp, int fd)
{
	t_var	*temp;

	temp = envp;
	while(temp != NULL)
	{
		write(fd, temp->name, ft_strlen(temp->name));
		if (temp->content != NULL)
		{
			write(fd, "=", 1);
			write(fd, temp->content, ft_strlen(temp->content));
		}
		write(fd, "\n", 1);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

// int	exit_pre_handler(t_node *node, int fd)
// {
// 	char	*check_input;
	
// 	if (ft_strlen("exit") == ft_strlen(node->full_cmd))
// 	{
// 		exit_shell(0);
// 		ft_putstr_fd("exit\n", fd, NULL);	
// 	}
// 	else
// 	{
// 		check_input = &(node->full_cmd[ft_strlen("exit") + 1]);
// 		if (*check_input == '+' || *check_input == '-')
// 			check_input++;
// 		while (*check_input != '\0')
// 		{
// 			if (*check_input >= '0' && *check_input <= '9')
// 				check_input++;
// 			else
// 			{
// 				ft_putstr_fd("exit\n", fd, NULL);
// 				if (*check_input == ' ')
// 				{
// 					exec_error(EXIT_NUM_ERROR, &(node->full_cmd[ft_strlen("exit") + 1]));
// 					return (1);
// 				}
// 				exec_error(EXIT_ARG_ERROR, &(node->full_cmd[ft_strlen("exit") + 1]));
// 				exit_shell(255);
// 			}
// 		}
// 		ft_putstr_fd("exit\n", fd);
// 		exit_shell(ft_atoi(&(node->full_cmd[ft_strlen("exit") + 1])));
// 	}
// 	return(0);
// }

int	check_following_builtin (t_node *node)
{
	t_node *node_tmp;
	
	if (node == NULL)
		return (0);
	node_tmp = node->next;
	while (node_tmp != NULL)
	{
		if (ft_strcmp(node_tmp->full_path, "builtin") == 0)
			return (1);
		node_tmp = node_tmp->next;
	}
	return (0);
}


int	builtin_caller(t_node *node, t_executor *executor, t_var *envp)
{
	// while (executor->pipes > 0 && read(executor->pipe[0], NULL, 1) > 0)
	// 	continue;
	if (ft_strncmp(node->full_cmd, "cd", ft_strlen("cd")) == 0)
		executor->status = cd(envp, &(node->full_cmd[ft_strlen("cd") + 1]), node->fd_out);
	else if (ft_strncmp(node->full_cmd, "echo", ft_strlen("echo")) == 0)
		executor->status = echo(&(node->full_cmd[ft_strlen("echo") + 1]), node->fd_out);
	else if (ft_strncmp(node->full_cmd, "pwd", ft_strlen("pwd")) == 0)
		executor->status = pwd(node->fd_out);
	else if (ft_strncmp(node->full_cmd, "export", ft_strlen("export")) == 0)
		executor->status = export_handler(&(node->full_cmd[ft_strlen("export") + 1]), envp, node->fd_out);
	else if (ft_strncmp(node->full_cmd, "unset", ft_strlen("unset")) == 0)
		executor->status = unset(&(node->full_cmd[ft_strlen("unset") + 1]), envp);
	else if (ft_strncmp(node->full_cmd, "env", ft_strlen("env")) == 0)
		executor->status = env(envp, node->fd_out);
	else if (ft_strncmp(node->full_cmd, "exit", ft_strlen("exit")) == 0)
		executor->status = 0;
		// executor->status = exit_pre_handler(node, node->fd_out);
	else
	{
		perror("builtin not found");
		executor->status = 1;
	}
	if (!(node->fd_out== 1))
	{
		if(dup2(executor->fd_out_original, 1) < 0)
			perror("Dup 2 restore output error");
		close(executor->fd_out_original);
		node->fd_out= 1;
		executor->fd_out_original = dup(1);
	}
	if (!(node->fd_in == 0))
	{
		if(dup2(executor->fd_in_original, 0) < 0)
			perror("Dup 2 restore output error");
		close(executor->fd_in_original);
		node->fd_in = 0;
		executor->fd_in_original = dup(0);
	}
	return (executor->status);
}