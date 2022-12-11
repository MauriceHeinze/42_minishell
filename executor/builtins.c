/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:33:17 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/11 13:55:17 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../inc/minishell.h"

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

int	exp_h(char *export, t_var *envp, int fd)
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

int	builtin_caller(t_node *n, t_executor *ex, t_var *envp)
{
	if (ft_strncmp(n->full_cmd, "cd", ft_strlen("cd")) == 0)
		ex->status = cd(envp, &(n->full_cmd[ft_strlen("cd") + 1]), n->fd_out);
	else if (ft_strncmp(n->full_cmd, "echo", ft_strlen("echo")) == 0)
		ex->status = echo_lat(&(n->full_cmd[ft_strlen("echo") + 1]), n->fd_out);
	else if (ft_strncmp(n->full_cmd, "pwd", ft_strlen("pwd")) == 0)
		ex->status = pwd(n->fd_out);
	else if (ft_strncmp(n->full_cmd, "export", ft_strlen("export")) == 0)
		ex->status = exp_h(&(n->full_cmd[ft_strlen("export") + 1]),
				envp, n->fd_out);
	else if (ft_strncmp(n->full_cmd, "unset", ft_strlen("unset")) == 0)
		ex->status = unset(&(n->full_cmd[ft_strlen("unset") + 1]), envp);
	else if (ft_strncmp(n->full_cmd, "env", ft_strlen("env")) == 0)
		ex->status = env(envp, n->fd_out);
	else if (ft_strncmp(n->full_cmd, "exit", ft_strlen("exit")) == 0)
		ex->status = exit_pre_handler(n, n->fd_out);
	else
		builtin_error(BULTIN_NF_ERROR, NULL);
	if (n->fd_out != 1 && n->fd_out_found == 1)
		close (n->fd_out);
	if (n->fd_in != 0 && n->fd_in_found == 1)
		close (n->fd_out);
	return (ex->status);
}
