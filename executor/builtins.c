/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:33:17 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/10 22:32:51 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../inc/minishell.h"

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

char	*echo_pre(char *str, int *n)
{
	int		num_n;

	*n = 0;
	num_n = 0;
	while ((ft_strncmp(&(str[num_n]), "-", 1) == 0))
	{
		num_n += 1;
		if ((ft_strncmp(&(str[num_n]), "n", 1) != 0))
			break ;
		while ((ft_strncmp(&(str[num_n]), "n", 1) == 0))
			num_n += 1;
		if (str[num_n] != '\0' &&(ft_strncmp(&(str[num_n]), " ;", 2) != 0))
			break ;
		else
		{
			str += 2;
			str += num_n;
			num_n = 0;
			*n = 1;
		}
	}
	return (str);
}

int	echo_move(char *str, int *isq, int *idq)
{
	if (*str == '\"' && !isq)
	{
		if (*idq)
			*idq = 0;
		else if (!(*idq))
			*idq = 1;
		str++;
		return (1);
	}
	else if (!(*idq) && *str == '\'')
	{
		if (*isq)
			*isq = 0;
		else if (!(*isq))
			*isq = 1;
		str++;
		return (1);
	}
	return (0);
}

int	echo_lat(char *str, int fd)
{
	int		isq;
	int		idq;
	int		n;

	n = 0;
	str = echo_pre(str, &n);
	isq = 0;
	idq = 0;
	while (*str != '\0')
	{
		if (echo_move(str, &isq, &idq))
			continue ;
		else if (*str == ';' && !isq && !idq)
			str++;
		else
			write(fd, str++, 1);
	}
	if (!n)
		write(fd, "\n", 1);
	return (EXIT_SUCCESS);
}

void	chdir_subhandler(t_var *envp, char *dir, char	**first_arg, char *cwd)
{
	if (dir == NULL || *dir == '\0')
	{
		if (chdir (get_env(envp, "HOME")) == -1)
			perror("chdir failed");
	}
	else
	{
		first_arg = ft_split(dir, ' ');
		if (chdir (*first_arg) == -1)
			perror("chdir failed");
	}
}

int	cd(t_var *envp, char *dir, int fd)
{
	char	**first_arg;
	char	cwd[PATH_MAX];

	first_arg = NULL;
	if (getcwd(cwd, PATH_MAX) == NULL)
		perror("getcwd failed");
	if (ft_strcmp(dir, "-") == 0)
	{
		if (chdir (get_env(envp, "OLDPWD")) == -1)
			perror("bash: cd: OLDPWD not set");
		pwd(fd);
	}
	else
		chdir_subhandler(envp, dir, first_arg, cwd);
	if (add_env(envp, ft_strdup("OLDPWD"), ft_strdup(cwd)) == NULL)
		perror("add_env failed");
	if (getcwd(cwd, PATH_MAX) == NULL)
		perror("getcwd failed");
	if (add_env(envp, ft_strdup("PWD"), ft_strdup(cwd)) == NULL)
		perror("add_env failed");
	if (first_arg != NULL)
		free_double_ptr(first_arg, 1);
	return (EXIT_SUCCESS);
}

char	*export_content(char *export)
{
	int		lc;
	char	*content;

	lc = 0;
	if (export[lc] == '\0' && export[lc] == ' ' && export[lc] == ';')
		perror("blala");
	while (export[lc] != '\0' && export[lc] != ' ' && export[lc] != ';')
		lc++;
	content = malloc(sizeof(char) * (lc + 1));
	ft_strlcpy(content, export, lc + 1);
	content[lc] = '\0';
	return (content);
}

int	export_print(t_var *envp, int fd)
{
	t_var	*temp;

	temp = envp;
	while (temp != NULL)
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
	if (!((*export >= 'A' && *export <= 'Z')
			|| (*export >= 'a' && *export <= 'z')))
	{
		perror("EXPORT");
		return (EXIT_FAILURE);
	}
	else
	{		
		length_name = 0;
		while (export[length_name] != '\0' && export[length_name] != '='
			&& export[length_name] != ' ' && export[length_name] != ';')
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

int	length_until_semicolon(char *str)
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
	int	exit_code;

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

	if (remove == NULL)
		return (EXIT_SUCCESS);
	i = 0;
	remove_split = ft_split(remove, ';');
	while (remove_split[i] != NULL)
	{
		c = 0;
		while (remove_split[i][c] != '\0')
		{
			if (remove_split[i][c] == ' ')
				remove_split[i][c] = '\0';
			c++;
		}
		remove_env(envp, remove_split[i++]);
	}
	while (i >= 0)
		free(remove_split[i--]);
	free(remove_split);
	return (EXIT_SUCCESS);
}

int	env(t_var *envp, int fd)
{
	t_var	*temp;

	temp = envp;
	while (temp != NULL)
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

int	check_following_builtin(t_node *node)
{
	t_node	*node_tmp;

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
	if (ft_strncmp(node->full_cmd, "cd", ft_strlen("cd")) == 0)
		executor->status = cd(envp, &(node->full_cmd[ft_strlen("cd") + 1]), node->fd_out);
	else if (ft_strncmp(node->full_cmd, "echo", ft_strlen("echo")) == 0)
		executor->status = echo_lat(&(node->full_cmd[ft_strlen("echo") + 1]), node->fd_out);
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
	else
	{
		perror("builtin not found");
		executor->status = 1;
	}
	if (node->fd_out != 1 && node->fd_out_found == 1)
		close (node->fd_out);
	if (node->fd_in != 0 && node->fd_in_found == 1)
		close (node->fd_out);
	return (executor->status);
}
